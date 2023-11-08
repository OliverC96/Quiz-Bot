//vcpkg from GitHub won't allow use to commit and push to BitBucket
// External Library curl folder won't commit and push to BitButcket

// ** BELOW is the ERROR messge we get when trying to push **

//22:43:40.365: [vcpkg] git -c credential.helper= -c core.quotepath=false -c log.showSignature=false push --progress --porcelain origin refs/heads/master:master
//        remote: Permission to Microsoft/vcpkg.git denied to taekim135.
//fatal: unable to access 'https://github.com/Microsoft/vcpkg.git/': The requested URL returned error: 403
//22:43:45.075: [vcpkg] git -c credential.helper= -c core.quotepath=false -c log.showSignature=false push --progress --porcelain origin refs/heads/master:master
//        remote: Permission to Microsoft/vcpkg.git denied to taekim135.
//fatal: unable to access 'https://github.com/Microsoft/vcpkg.git/': The requested URL returned error: 403