pkgname=nauz-file-detector
pkgver=0.10
pkgrel=1
pkgdesc='Nauz File Detector(NFD) is a linker/compiler/packer identifier utility'
arch=('x86_64')
url='https://horsicq.github.io'
license=(MIT)
provides=(
  'nauz-file-detector'
)
conflicts=(
  'nauz-file-detector'
)
depends=(
  'freetype2'
  'glib2'
  'glibc'
  'graphite'
  'icu'
  'krb5'
  'qt5-base'
  'systemd-libs'
)
makedepends=(
  'coreutils'
  'git'
  'imagemagick'
  'qt5-tools'
)
_srcname="Nauz-File-Detector"
source=(
  'git+https://github.com/horsicq/Nauz-File-Detector.git'
)
sha512sums=(
  'SKIP'
)
_pkgname="${pkgname/-git/}"
_stop='\e[m'
_color="\e[33m"
_bold='\e[1m'
_prefix=" ${_bold}${_color}==>${_stop} "

prepare() {
    cd "$srcdir/$_srcname"
    git submodule update --init --recursive
}

build() {
  cd "$_srcname" || return
  echo -e "${_prefix}nauz-file-detector"

  _subdirs="build_libs gui_source console_source"

  # [DEPRECATED] FIXME UPSTREAM: -Werror=format-security is causing build errors (merged upstream)
  #export CFLAGS+=" -Wno-format-security"
  #export CXXFLAGS+=" -Wno-format-security"

  for _subdir in $_subdirs; do
    pushd "$_subdir" || return
    echo -e "${_prefix}${_prefix}Building $_subdir"
    qmake-qt5 PREFIX=/usr QMAKE_CFLAGS="${CFLAGS}" QMAKE_CXXFLAGS="${CXXFLAGS}" QMAKE_LFLAGS="${LDFLAGS}" "$_subdir.pro"
    make -f Makefile clean
    make -f Makefile
    popd || return
  done
}

package() {
  cd "$_srcname" || return

  echo -e "${_prefix}Creating the package base"
  install -d "$pkgdir"/{opt/"${_pkgname}",usr/bin,usr/share/pixmaps}
  install -d "$pkgdir/opt/${_pkgname}"/{qss,images}

  echo -e "${_prefix}Copying the package binaries"
  install -Dm 755 build/release/nfd -t "$pkgdir"/opt/"${_pkgname}"
  install -Dm 755 build/release/nfdc -t "$pkgdir"/opt/"${_pkgname}"
  
  echo -e "${_prefix}Copying the package files"
  install -Dm 644 XStyles/qss/* -t "$pkgdir"/opt/"${_pkgname}"/qss
  cp -r images/* -t "$pkgdir"/opt/"${_pkgname}"/images/

  echo -e "${_prefix}Setting up /usr/bin launchers"
  ln -s /opt/"${_pkgname}"/nfd "$pkgdir"/usr/bin/nfd
  ln -s /opt/"${_pkgname}"/nfdc "$pkgdir"/usr/bin/nfdc

  echo -e "${_prefix}Setting up desktop icon"
  install -Dm 644 LINUX/hicolor/48x48/apps/nfd.png -t "$pkgdir"/usr/share/pixmaps

  echo -e "${_prefix}Setting up desktop shortcuts"
  install -Dm 644 LINUX/nfd.desktop -t "$pkgdir"/usr/share/applications
  
  install -Dm 644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
