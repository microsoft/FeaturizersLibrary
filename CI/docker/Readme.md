Building the Image
==================
These are the steps required to build an image locally and push it to an Azure
Container Registry so that it can be used during builds.

    1) Build the image:

            python Build.py Build <image_name>

    2) Login to the ACR:

            docker login --username featurizerslibrarybuild --password-stdin featurizerslibrarybuild.azurecr.io

            Where '<password>` can be found by:

                a) Log into the Azure portal
                b) Navigate to the 'featurizerbuild' ACR resource
                c) Select 'Access Keys'
                d) Copy the value for 'password'

    3) Publish the image:

            python Build.py Publish <image_name> featurizerslibrarybuild.azurecr.io

Note that ../PR.yaml and ../CI.yaml (and potentially other files) are configured to use
this image in this Container Registry.
