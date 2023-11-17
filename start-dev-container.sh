#!/bin/bash

podman run -it --rm \
    --net=host \
    -v $PWD:/work \
    -w /work \
    --security-opt label=disable \
    rlenferink/yaml-cpp-example:latest \
    bash
