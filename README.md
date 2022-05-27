# scrycli
CLI tool for Scryfall
## Dependencies
[libscry](https://github.com/EmperorPenguin18/libscry), chafa
## Installation

Arch

```
git clone https://github.com/EmperorPenguin18/scrycli
cd scrycli
makepkg -si
```
Or just install from the [AUR](https://aur.archlinux.org/packages/scrycli)

Other Linux

```
git clone https://github.com/EmperorPenguin18/scrycli
cd scrycli
make release
make install #as root
```

## Usage

```
scrycli [OPTION...] SEARCH...
```
Read the man page for more info

## Uninstallation

Arch

```
pacman -R scrycli #as root
```

Other Linux

```
cd scrycli
make uninstall #as root
```
