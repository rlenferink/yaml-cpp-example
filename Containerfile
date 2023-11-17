FROM registry.access.redhat.com/ubi8/ubi:8.8-1067.1698056881

RUN dnf install -y \
        cmake \
        gcc \
        gcc-c++ \
        git \
        wget && \
    dnf clean all
        
