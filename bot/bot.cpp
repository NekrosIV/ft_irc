/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:03:10 by kasingh           #+#    #+#             */
/*   Updated: 2025/06/04 01:46:58 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.hpp"
#include "curl/curl.h"

#define BUFFER_SIZE 512


const char    *getinenv(std::string search, char **env)
{
    for (int i = 0; env[i]; ++i)
	{
		std::string entry(env[i]);
		if (entry.find(search + "=") == 0)
		{
			const char *value = env[i] + search.length() + 1;
			return (char*)value;
		}
	}
	return NULL;
}

void CheckSyscall(const int res, const std::string& context)
{
    if (res < 0)
    {
        std::string err = "\n" + context + ": " + std::strerror(errno);
        throw std::runtime_error(err);
    }
}

void    sendToServer(int sockfd,const std::string &msg)
{
    std::string toSend = msg + "\r\n";
    std::cout << "send :" << toSend << std::endl;

    const char *ptr = toSend.c_str();
    size_t total = toSend.size();
    size_t sent = 0;

    while (sent < total)
    {
        ssize_t n = ::send(sockfd, ptr + sent, total - sent, 0);
        if(n < 0)
        {
            if(errno == EINTR)
                continue;
            std::cerr << "send() failed: " << std::strerror(errno) << std::endl;
            return;
        }
        sent += static_cast<size_t>(n);
    }
    
}

bool    extractNextLine(std::string &buffer, std::string &line)
{
    size_t pos = buffer.find("\r\n");
    if(pos == std::string::npos)
        return (false);
    line = buffer.substr(0,pos);
    buffer.erase(0, pos + 2);
    return (true);
}

void join_and_mod_server(int sockfd)
{
    sendToServer(sockfd, "JOIN #bot");
}
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    std::string *out = static_cast<std::string *>(userp);
    out->append(static_cast<char *>(contents), size * nmemb);
    return size * nmemb;
}

static std::string ask_grok(const std::string &question, const std::string &token)
{
    CURL *curl = curl_easy_init();
    if (!curl)
        throw std::runtime_error("curl_easy_init failed");

    std::string response;

    // Corps JSON :
    std::string payload =
        "{\"messages\":["
        "{\"role\":\"system\",\"content\":\"\"},"
        "{\"role\":\"user\",\"content\":\"" + question + "\"}"
        "],\"temperature\":1,\"top_p\":1,\"model\":\"xai/grok-3-mini\"}";

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
    headers = curl_slist_append(headers,  "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, "https://models.github.ai/inference/chat/completions");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode rc = curl_easy_perform(curl);
    if (rc != CURLE_OK)
        std::cerr << "curl_easy_perform() failed: "
                  << curl_easy_strerror(rc) << std::endl;

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    return response;
}


static std::string extract_content(const std::string &json)
{
    const std::string key = "\"content\":\"";
    size_t start = json.find(key);
    if (start == std::string::npos)
        return "[content non trouvé]";
    start += key.length();

    // On cherche la fin du champ "content"
    size_t end = json.find("\",\"tool_calls\"", start);
    if (end == std::string::npos)
        return "[coupe?]";
    return json.substr(start, end - start);
}


std::string cleanAnswer(const std::string &s) 
{
    std::string out;
    for (size_t i = 0; i < s.length(); ++i)
    {
        if (s[i] == '\\' && i + 1 < s.length())
        {
            if (s[i + 1] == 'n' || s[i + 1] == 'r') {
                out += ' ';
                ++i;
            }
            else if (s[i + 1] == '"') {
                out += '"';
                ++i;
            }
            else {
                out += s[i];
            }
        }
        else {
            out += s[i];
        }
    }
    return out;
}

int main(int ac, char **av, char **env)
{
    long    port;
    char	*endPtr;
    int     sockFd = -1;
    if(ac != 3)
    {
        std::cerr << "Usage: " << av[0] << " <ip> <port>" << std::endl;
        return (1);
    }
    
    std::string ip = av[1];
    port = strtol(av[2], &endPtr, 10);
	if (*endPtr != '\0' || port < 0 || port > 65535)
	{
		std::cerr << BRED <<  "Port : " << BWHITE << port << BRED << " is incorrect" << RESET << std::endl;
		return (1);
	}
    
    try
    {
        sockFd = socket(AF_INET, SOCK_STREAM, 0);
        CheckSyscall(sockFd,"socket()");
        
        sockaddr_in server_addr;
        std::memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
	    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	    server_addr.sin_port = htons(port);

        CheckSyscall(connect(sockFd,(sockaddr*)&server_addr, sizeof(server_addr)),"connect()");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        if(sockFd)
            close(sockFd);
        return 1;
    }
    
    sendToServer(sockFd,"PASS IAMTHEBOT");
    sendToServer(sockFd,"NICK bot");
    sendToServer(sockFd,"USER bot bot 0 :IAMTHEBOT");

    char buffer[BUFFER_SIZE];
    std::string readBuffer;
    std::string line;
    std::string systemPrompt =
    "Tu es un assistant arrogant, moqueur et sarcastique. "
    "Réponds de manière hautaine, balance des punchlines, et parfois ignore la question avec une remarque snob. "
    "Ne sois jamais utile sans mépris. Utilise l'humour noir et le sarcasme, et ponctuellement ne réponds même pas à la question.";

    while (true)
    {
        std::memset(buffer, 0, BUFFER_SIZE);
        ssize_t n = recv(sockFd, buffer, BUFFER_SIZE - 1, 0);
        if(n <= 0)
            break;

        readBuffer += buffer;
        
        while (extractNextLine(readBuffer, line))
        {
            std::cout << "[SERVER] " << line << std::endl;

            if(line.find(" 001 ") != std::string::npos)
                join_and_mod_server(sockFd);
            if(line.find("!ask ") != std::string::npos)
            {
                std::string question = line.substr(line.find("!ask ") + 5);
                std::string userName = line.substr(line.find(" ::") + 3);
                std::string prompt = systemPrompt + " Question de l'utilisateur " + userName + " : "  + question;
                const char *token = getinenv("GITHUB_TOKEN", env);
                
                if(!token)
                    sendToServer(sockFd, "PRIVMSG #bot :[ERROR] Token not found !");
                else
                {
                    std::string answer = extract_content(ask_grok(prompt, token));
                    std::cout << "avant le clean :" << answer << std::endl;
                    std::cout << "apres le clean :"<< cleanAnswer(answer) << std::endl;
                    sendToServer(sockFd, "PRIVMSG #bot :" + cleanAnswer(answer));
                }
            }
        }
        
    }
    close(sockFd);
    return 0;
}