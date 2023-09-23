# Maintainer: Samuel Dawant <samueld@mailo.com>
pkgname=zenowl-dwm
pkgver=6.3
pkgrel=1
pkgdesc="zenowl version of dwm"
arch=(x86_64)
url="git@github.com:BrachystochroneSD/dwm.git"
license=('GPL')
provides=(st)
source=(
  config.def.h
  config.mk
  drw.c
  drw.h
  dwm.1
  dwm.c
  Makefile
  transient.c
  util.c
  util.h
  vanitygaps.c
)
sha256sums=('065f484f65eccd2dabf7e893a0710b131ced7b4eebb2ccd3b34bf3e0d62e8ee9'
            'ef25274594d8b381a2f0ba6c76b88583abebe7004794d73e387a7494f142fabc'
            '7b8d62f7846b42f61bdfd9c5d7f8db3e10944916461fbd8e54379243454def92'
            '7d93583ca3d06e09007d0381361f7a6423bfd6438db4d508fe38095f36dbc4e6'
            'e97f42257c05b7298a15a57c5a579b534ab37a305fc3bdc6f2c9d04788f3ab51'
            'acc86c92dd5b509988b9ae016eb0f28cbee3cbce01e1b3cfcc23cb73f0779e1d'
            '3f25d0e9b090f9b54d57abdc563641e25aaae3c1452005ba3701152eab1b6944'
            '54c37c558613ab3da856b19c4b4c0c56c224133a253bf5fa6557b489da545d7c'
            'dec870d0b5834c9008ff62f495710daf524cffdf12d0cf8ba4fadf5643623987'
            '1196a7b6efbf4cb3f5c435fffd72e7647f977483845d5c78c1c48d9ab8b96819'
            '1fddab0262ae8080966027af5adf8622dbd4f33728068fafda4d1c0338a60426')

build() {
    make
}

package() {
    make DESTDIR="$pkgdir/" install
}
