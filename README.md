# Cornell ttH repository


## Documentation

A package-specific documentation (README.md) should be placed inside the
package.


## Structure

* analyzers: a place/namespace to keep analyzers.

* external: external packages should be here. A good place for git submodules.

* githooks: a place for custom git hooks. They can be autolinked by the init.sh
script.

* local: a place for local installations. Should be kept empty in a repo, but
is used otherwise.

* script: shell (helper) scripts live here.

* util: a place to keep standalone utilities.


## Setup

Start with script/setup/init.sh that will help to set up some basics.
