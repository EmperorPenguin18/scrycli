# Maintainer: Sebastien MacDougall-Landry

pkgname=scrycli
pkgver=0.1
pkgrel=1
pkgdesc='CLI tool for Scryfall'
url='https://github.com/EmperorPenguin18/scrycli/'
source=("$pkgname-$pkgver.tar.gz::https://github.com/EmperorPenguin18/scrycli/archive/refs/tags/$pkgver.tar.gz")
arch=('x86_64')
license=('GPL3')
makedepends=('pandoc')
depends=('libscry')
sha256sums=('')

build () {
  cd "$srcdir/$pkgname-$pkgver"
  g++ -std=c++20 scrycli.cc -ldl -o scrycli
  pandoc scrycli.1.md -s -t man -o scrycli.1
}

package () {
  cd "$srcdir/$pkgname-$pkgver"
  install -Dm755 scrycli -t "$pkgdir/usr/bin"
  install -Dm644 $startdir/scrycli.1 -t "$pkgdir/usr/share/man/man1"
}
