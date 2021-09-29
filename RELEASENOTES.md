# Summary of changes

## Changes for version 1.1.5 (29 Sep 2021)

### Bug Fixes

- Executed existing unit tests as part of Jenkins continuous integration


## Changes for version 1.1.4 (29 Sep 2021)

### Bug Fixes

- Added configurations for the Snow project into continuous integration


## Changes for version 1.1.3 (14 Sep 2021)

### Bug Fixes

- Moved continuous integration to Jenkins
- Deploy conan package into remote specific for C++ task force
- Fixed use of "export_sources" definition in conan recipe


## Changes for version 1.1.2 (30 Mar 2021)

### Bug Fixes

- Upload generated packages to CSW JFrogPlatform
- Moved VS2017 configurations to work with GoogleTest 1.10.0


## Changes for version 1.1.1 (25 Feb 2021)

### Bug Fixes

- Updated continuous integration to:
  - Use GitHub Action to generate library documentation
  - Upload generated packages to Systelab's public Artifactory


## Changes for version 1.1.0 (7 Sep 2020)

### Enhancements

- Added pretty serialization
- Support for JSON pointers


## Changes for version 1.0.9 (25 Aug 2020)

### Bug Fixes

- Fixed memory leak when using remote schema documents


## Changes for version 1.0.8 (2 Jun 2020)

### Bug Fixes

- Used gtest package from conan-center (without username / channel)


## Changes for version 1.0.7 (18 Apr 2020)

### Bug Fixes

- Added method to build a new document from a value


## Changes for version 1.0.6 (15 Jan 2020)

### Bug Fixes

- Fixed compilation for GoogleTest 1.10.0
- Fixed compilation for Visual Studio 2019


## Changes for version 1.0.5 (8 Dec 2019)

### Bug Fixes

- Moved JSONAdapterInterface dependency to version 1.0.8
- Added missing unit tests to cover JSON schema validation features


## Changes for version 1.0.4 (9 Nov 2019)

### Bug Fixes

- Moved to version 1.0.4 of interface (added methods to handle NULL values easily)
- Fixed Codacy issues


## Changes for version 1.0.3 (22 Oct 2019)

### Bug Fixes

- Retrieve interface and test utilities from new conan packages of JSONAdapter repository.


## Changes for version 1.0.2 (10 Oct 2019)

### Bug Fixes

- Updated compilation configurations to include the ones required for the Snow project


## Changes for version 1.0.1 (3 Jul 2019)

### Bug Fixes

- Improved cmake and conan configuration to link only against used dependencies.


## Changes for version 1.0.0 (4 Apr 2019)

### Enhancements

- Initial version in Github (ported from internal SVN server)
