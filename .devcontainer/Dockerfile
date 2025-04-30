# Use an official lightweight base image
FROM  --platform=linux/amd64 debian:bullseye-slim

# Install necessary tools
RUN apt-get update && apt-get install -y \
	build-essential \
	curl \
	gcc \
	gdb \
	make \
	lldb \
	xorg \
	libx11-dev \
	libxext-dev \
	libbsd-dev \
	libxext-dev \
	zlib1g-dev \
	libbsd-dev \
	git \
	pkg-config \
	zsh \
	tmux \
	fzf \
	&& rm -rf /var/lib/apt/lists/*

# Download the joestar setup script
RUN curl -fsSL https://raw.githubusercontent.com/ollie-joestar/dotfiles_mini/main/setup.sh -o /usr/local/bin/joestar && \
	chmod +x /usr/local/bin/joestar
