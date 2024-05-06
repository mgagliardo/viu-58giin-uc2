FROM alpine:latest

WORKDIR /uc2

RUN apk update && \
    apk upgrade --no-cache && \
    apk add  --no-cache flex bison openjdk21-jdk gcc g++ make automake && \
    rm /var/cache/apk/*

COPY . .

RUN make clean all

ENTRYPOINT ["./entrypoint.sh"]
