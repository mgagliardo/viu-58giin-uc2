FROM ubuntu:jammy

WORKDIR /uc2

# Install software
RUN apt update && \
    apt upgrade -y && \
    apt install -y flex bison openjdk-21-jdk gcc &&
    apt clean all &&
    rm -rf /var/lib/apt/*

COPY lex.l syntax.y Makefile tests/ .

CMD ["make", "clean", "all"]
