#!/bin/sh

cd -- "$( dirname -- "${BASH_SOURCE[0]}" )"

# Create a ZIP file with the same name as the directory
zip -r "nhf.zip" *.c *.h owners animals treatments *.pdf

# Check if the ZIP file was created successfully
if [ $? -eq 0 ]; then
  echo "ZIP file created successfully."
else
  echo "Failed to create ZIP file."
fi
