# A Dockerfile that creates a fairly cut down Ubuntu 24 image that can be
# used to build, run and debug the mud and its related tools. 
# See README.md in this directory.
FROM ubuntu:latest
RUN \
 echo 'Acquire::http::Timeout "5";\nAcquire::ftp::Timeout "5";\n;' > /etc/apt/apt.conf.d/99timeout && \
 apt-get -qq update && \
 DEBIAN_FRONTEND="noninteractive" apt-get -y --no-install-recommends install  \
 dialog tzdata sudo locales tmux  wget curl gnupg git-core iputils-ping ssh \
 build-essential software-properties-common cmake ninja-build telnet rlwrap \
 gdb less ripgrep powerline clangd-19 clang-tidy-19 clang-19 clang-tools-19 pip

RUN \
 add-apt-repository ppa:neovim-ppa/unstable -y && \
 apt-get -qq update && \
 DEBIAN_FRONTEND="noninteractive" apt-get -y install neovim
RUN \
 update-alternatives --install /usr/bin/vim vim $(which nvim) 10 && \
 update-alternatives --install /usr/bin/vi vi $(which nvim) 10 && \
 update-alternatives --install /usr/bin/editor editor $(which nvim) 10 && \
 update-alternatives --install /usr/bin/clangd clangd $(which clangd-19) 10 && \
 update-alternatives --install /usr/bin/clang clang $(which clang-19) 10 && \
 update-alternatives --install /usr/bin/clang++ clang++ $(which clang++-19) 10 && \
 update-alternatives --install /usr/bin/clang-tidy clang-tidy $(which clang-tidy-19) 10

RUN locale-gen en_US.UTF-8 en_GB.UTF-8 && \
    update-locale LANG=en_US.UTF-8 LANGUAGE=en_US LC_ALL=en_US.UTF-8 && \
    adduser \
        --quiet \
        --disabled-password \
        --shell /usr/bin/bash \
        --home /home/mudder \
        --gecos "Mudder" mudder && \
    usermod -aG sudo mudder

RUN /usr/bin/echo -e '\
export EDITOR=nvim\n\
export GREP_COLORS="fn=37"\n\
export GPG_TTY=$(tty)\n\
export TERM=xterm-256color\n\
export LC_ALL=en_US.UTF-8\n\
export LANG=en_US.UTF-8\n\
powerline-daemon -q\n\
' > /etc/profile.d/terminal.sh

RUN /usr/bin/echo -e '\
bind | split-window -h\n\
bind - split-window -v\n\
' > /etc/tmux.conf

RUN --mount=type=secret,id=mudpass \
    echo "mudder:`cat /run/secrets/mudpass`" | chpasswd

ENV NVM_DIR=/usr/local/nvm
RUN mkdir $NVM_DIR \
    && curl https://raw.githubusercontent.com/creationix/nvm/master/install.sh | bash \
    && . $NVM_DIR/nvm.sh \
    && nvm install node
RUN . $NVM_DIR/nvm.sh \
    && npm install -g pyright typescript-language-server typescript

USER mudder
WORKDIR /home/mudder
ENV LC_ALL=en_US.UTF-8
ENV LANG=en_US.UTF-8
ENTRYPOINT ["bash", "--login"]
