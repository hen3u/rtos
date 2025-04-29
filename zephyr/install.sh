#!/bin/bash +x

SDK_VERSION:=0.16.9

sudo apt install -y python3-venv
python3 -m venv .venv
source .venv/bin/activate
pip install  west
wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${SDK_VERSION}/zephyr-sdk-${SDK_VERSION}_linux-x86_64.tar.xz
tar xf zephyr-sdk-${SDK_VERSION}_linux-x86_64.tar.xz
cd zephyr-sdk-${SDK_VERSION}/
./setup.sh
cd ..
rm zephyr-sdk-${SDK_VERSION}_linux-x86_64.tar.xz


