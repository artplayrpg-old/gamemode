FROM southclaws/sampctl:1.8.39

ADD . .

RUN sampctl package ensure && \
    sampctl package build && \
    apt update && apt install -y libuuid1:i386 uuid-dev:i386

ENTRYPOINT [ "sampctl", "package", "run" ]