---
services: storage
platforms: javascript
author: Jin
---

# Static Website - File Browser app for Blob Storage

This single-page-app hosted on Azure storage static website: https://featurizerslibrarybuild.z5.web.core.windows.net/ is used to let users to browse all builds files on Azure Storage account.

# Original design

The original intention is to have a link for latest release and a link for the most recent build. The static website hosted by Azure storage would point to the link for the most recent build, Latest_build/index.html. This requires uploading Artifacts to a specific folder whenever a new build is finished and since this process involves deleting previous build Artifacts and uploading new Artifacts, there would be a potential time window for the static website to be invalid.

Based on this reasoning, we designed several steps to minimize the time window:
- Upload build Artifact to both pipeline_product_version and Latest_build_${GUID} folder
- Rename Latest_build(which is created by prebious build) => Latest_build_old
- Rename Latest_build_${GUID} => Latest_build
- Delete Latest_build_old

However, Azure storage blob doesn't provide RENAME functionality and a blob cannot be renamed without cloning the folder which is against the intention of our design to minimize the time window.

Under this circumstance, we decided to use a single-page-app based on [Seguler's work on Github](https://github.com/seguler/static-website-blob-browser) which can browse all past builds.


## Deploy - step by step
Follow the following steps to deploy the app on Azure Storage account. Once deployed, the app will provide you a file browser view of the **archive** container.

This app uses [npm](https://www.npmjs.com/) (package manager for the JavaScript programming language runtime environment Node.js) to build. So please install the latest version of npm before you start.

- Launch VS Code. Log on to the Azure Storage extension.
- Install [create-react-app](https://github.com/facebook/create-react-app) using a terminal (VSCode)
`npm install -g create-react-app` in this folder
- Open the sample in VSCode using `File>Open Folder` menu
- On the terminal, run `npm install` and then `npm run build` to build the React app
- Right click `build` folder in VSCode, and click `Deploy to Static Website`
- Choose your storage account to deploy the static website

## More information
- [Azure Storage SDK for JS](https://github.com/azure/azure-storage-js)
- [Static Websites on Azure Storage](https://docs.microsoft.com/en-us/azure/storage/blobs/storage-blob-static-website)
- [Deploy a Static Website with VSCode](https://code.visualstudio.com/tutorials/static-website/getting-started)
