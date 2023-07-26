#!/bin/bash
exec sed -f filter-out-attrs.sed "$@"
