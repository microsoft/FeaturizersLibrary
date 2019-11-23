Publishing a New Image for CI
=============================
The Azure DevOps functionality that makes containers available during builds
assumes that `sudo` is available on the image. Unfortunately, the image that
we use for universal linux builds (`phusion/holy-build-box-64`) does not enable
`sudo` by default.

These are the steps required to build an image locally and push it to an Azure
Container Registry so that it can be used during builds.

    1) Build the image:

            python Build.py Build

    2) Login to the ACR:

            docker login --username featurizersbuild --password <password> featurizersbuild.azurecr.io

            Where '<password>` can be found by:

                a) Log into the Azure portal
                b) Navigate to the 'featurizerbuild' ACR resource
                c) Select 'Access Keys'
                d) Copy the value for 'password'

    3) Publish the image:

            python Build.py Publish featurizersbuild.azurecr.io

Note that ../PR.yaml and ../CI.yaml (and potentially other files) are configured to use
this image in this Container Registry.
