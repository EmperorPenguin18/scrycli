# Maintainer: Sebastien MacDougall-Landry

pkgname=scrycli
pkgver=0.2
pkgrel=1
pkgdesc='CLI tool for Scryfall'
url='https://github.com/EmperorPenguin18/scrycli/'
source=("$pkgname-$pkgver.tar.gz::https://github.com/EmperorPenguin18/scrycli/archive/refs/tags/$pkgver.tar.gz")
arch=('x86_64')
license=('GPL3')
makedepends=('pandoc')
depends=('libscry' 'chafa')
sha256sums=('72fb7097fc196a663b49408c2a405ab67b2fea1b47a72f9f5163fae6de283c98')

build () {
  cd "$srcdir/$pkgname-$pkgver"
  g++ -O3 src/*.cc -o scrycli
  pandoc scrycli.1.md -s -t man -o scrycli.1
}

package () {
  cd "$srcdir/$pkgname-$pkgver"
  install -Dm755 scrycli -t "$pkgdir/usr/bin"
  install -Dm644 scrycli.1 -t "$pkgdir/usr/share/man/man1"
}
