#!/bin/sh

set -euo pipefail

make run test=$@
