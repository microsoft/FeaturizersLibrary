These Azure DevOps build definitions rely on the following Service Connections.
To add/remove/view Service Connections within Azure DevOps:

    1) Navigate to Azure DevOps Project Page
    2) Project Settings -> Service connections

AI Infra Build
--------------
Used to push binaries to Azure resources during publish.

    Type:                                               Azure Resource Manager
    Connection Name:                                    AI Infra Build (<guid>)
    Scope level:                                        Subscription
    Subscription:                                       AI Infra Build (<guid>)
    Resource Group:                                     FeaturizersBuild

ESRP CodeSigning Connection
---------------------------
Used to sign binaries and packages.

    Type:                                               ESRP CodeSigning
    Server URL:                                         https://api.esrp.microsoft.com/api/v2
    AAD APP Id:                                         <created in Azure>
    AAD APP Secret:                                     <created in Azure>
    PRSS Signing Authentication Certificate:            Created through the [ESRP Portal](https://portal.esrp.microsoft.com/)

featurizersbuild
----------------
Used to pull the universal_linux Docker image for universal_linux builds.

    Type:                                               Dockerregistry
    Registry Type:                                      Azure Container Registry
    Connection name:                                    featurizersbuild
    Azure subscription:                                 AI Infra Build
    Azure container registry:                           featurizersbuild
