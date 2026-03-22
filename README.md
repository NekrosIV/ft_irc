# ft_irc

## Description

`ft_irc` is a custom IRC server written in C++98 for the 42 curriculum.
It implements a non-blocking TCP server with `epoll`, parses IRC-style commands, manages clients/channels in memory, and handles a core set of IRC commands.

## Features

- Non-blocking server loop using `socket`, `bind`, `listen`, `accept`, and `epoll`.
- Client registration flow with `PASS`, `NICK`, and `USER`.
- Implemented commands: `PASS`, `NICK`, `USER`, `PING`, `JOIN`, `PART`, `PRIVMSG`, `NOTICE`, `QUIT`, `KICK`, `INVITE`, `TOPIC`, `MODE`.
- Channel lifecycle management (create on join, delete when empty).
- Channel moderation and access controls through mode flags:
  - `+i` / `-i` invite-only
  - `+t` / `-t` topic restricted to operators
  - `+k` / `-k` channel key (password)
  - `+l` / `-l` user limit
  - `+o` / `-o` channel operator promotion/removal
- Numeric-style server replies and error replies for command validation cases.
- Optional bonus bot target (`make bonus`) using libcurl to connect and answer `!ask` messages in `#bot`.

## How It Works

At startup, the server opens a listening socket, sets it non-blocking, and registers it in an `epoll` instance.
When a new client connects, its fd is added to `epoll` and wrapped in a `Client` object.

Incoming data is buffered per client, split on IRC line endings (`\r\n`), then parsed by `parseIrcCommand`.
Each parsed command is dispatched through a command map (`std::map<std::string, CommandFunc>`) to its handler.

Channels are represented by `Channel` objects with member/operator/invite/ban sets and mode state.
Message delivery uses `TryToSend`; partial writes and `EWOULDBLOCK` are buffered and flushed when `EPOLLOUT` is available.

## Installation / Build

### Requirements

- Linux environment
- `c++` compiler with C++98 support
- `make`
- For `make bonus`: OpenSSL development libraries available to the linker (`-lssl`, `-lcrypto`)

### Build server

```bash
make
```

This creates the `ircserv` binary at repository root.

### Optional cleanup targets

```bash
make clean
make fclean
make re
```

### Optional bonus bot build

```bash
make bonus
```

This creates `ircbot` and links against bundled `bot/curl_local` libraries plus system SSL/crypto libraries.

## Usage

### Run the server

```bash
./ircserv <port> <password>
```

Example:

```bash
./ircserv 6667 supersecret
```

### Connect with an IRC client

Use any IRC client and connect to your server/port, then authenticate with the server password.

Minimal raw command flow after TCP connection:

```text
PASS supersecret
NICK alice
USER alice 0 * :Alice
JOIN #general
PRIVMSG #general :Hello from ft_irc
```

### Optional bot runtime

After building with `make bonus`:

```bash
export GITHUB_TOKEN="<your_token>"
./ircbot 127.0.0.1 6667
```

The bot authenticates with `PASS IAMTHEBOT`, uses nickname `bot`, joins `#bot`, and replies to `!ask` messages.

## Example

Example session with one channel:

```text
# Client A
PASS supersecret
NICK alice
USER alice 0 * :Alice
JOIN #team

# Client B
PASS supersecret
NICK bob
USER bob 0 * :Bob
JOIN #team
PRIVMSG #team :Hi Alice

# Client A
MODE #team +i
INVITE bob #team
TOPIC #team :Project kickoff
```

## Project Structure

```text
.
|-- include/
|   |-- Serveur.hpp      # Core server interface and command handlers
|   |-- Client.hpp       # Per-client state and I/O buffers
|   |-- Channel.hpp      # Channel state, members, operators, modes
|   `-- Utils.hpp        # Parsing and shared helpers
|-- src/
|   |-- main.cpp         # Program entry point
|   |-- Serveur.cpp      # Socket/epoll loop, dispatch, send/error helpers
|   |-- Client.cpp       # Client model and buffers
|   |-- Channel.cpp      # Channel model operations
|   |-- Utils.cpp        # IRC line parser and low-level helpers
|   `-- cmd*.cpp         # IRC command implementations
|-- bot/
|   `-- bot.cpp          # Optional IRC bot (bonus)
`-- makefile             # Build targets for server and bonus bot
```

## What I Learned

- Building a concurrent network service with non-blocking sockets and `epoll`.
- Designing command dispatch and protocol parsing for text-based protocols.
- Managing per-client and per-channel state safely across many events.
- Implementing IRC-like permissions and channel moderation rules.
- Handling partial writes, buffering, and disconnect paths in real-world server code.
