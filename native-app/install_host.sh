#!/bin/sh
# Copyright 2013 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
set -e
g++ pingpong.cpp -o pingpong -ljsoncpp  
DIR="$( cd "$( dirname "$0" )" && pwd )"
if [ "$(uname -s)" == "Darwin" ]; then
  if [ "$(whoami)" == "root" ]; then
    TARGET_DIR="/Library/Google/Chrome/NativeMessagingHosts"
  else
    TARGET_DIR="$HOME/Library/Application Support/Google/Chrome/NativeMessagingHosts"
  fi
else
  if [ "$(whoami)" == "root" ]; then
    TARGET_DIR="/etc/opt/chrome/native-messaging-hosts"
  else
    TARGET_DIR="$HOME/.config/google-chrome/NativeMessagingHosts"
  fi
fi
HOST_NAME=com.hashpire.pingpong
# Create directory to store native messaging host. If exists, do nothing.
mkdir -p "$TARGET_DIR"
# Copy native messaging host manifest.
cp "$DIR/$HOST_NAME.json" "$TARGET_DIR"
# Update host path in the manifest.
HOST_PATH=$DIR/pingpong
ESCAPED_HOST_PATH=${HOST_PATH////\\/}
sed -i -e "s/HOST_PATH/$ESCAPED_HOST_PATH/" "$TARGET_DIR/$HOST_NAME.json"
# Set permissions for the manifest so that all users can read it.
chmod o+r "$TARGET_DIR/$HOST_NAME.json"
echo "Native messaging host $HOST_NAME has been installed."