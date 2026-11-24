#!/bin/bash

read -p "fornavn?" fornavn


antall=$(cut -d: -f5 /etc/passwd|grep -i $fornavn|wc -l)

echo "antall brukere som har navnet $fornavn: $antall"


