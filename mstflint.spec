Name:		mstflint
Summary:	Mellanox firmware burning tool
Version:	4.9.0
Release:	3%{?dist}
License:	GPLv2+ or BSD
Group:		Applications/System
# Source downloaded from https://github.com/Mellanox/%{name}/releases/download/v%{version}-3/%{name}-%{version}.tar.gz
# Rename it as mstflint-4.9.0-3.tar.gz
Source: 	mstflint-4.9.0-3.tar.gz
Url:		https://github.com/Mellanox/mstflint
BuildRequires:	libstdc++-devel, zlib-devel, libibmad-devel, rdma-core-devel
BuildRequires:  libcurl-devel, boost-devel, libxml2-devel, openssl-devel
Obsoletes:	openib-mstflint <= 1.4 openib-tvflash <= 0.9.2 tvflash <= 0.9.0
ExcludeArch:	s390 s390x

%description
This package contains firmware update tool, vpd dump and register dump tools
for network adapters based on Mellanox Technologies chips.

%prep
%setup -q
find . -type f -iname '*.[ch]' -exec chmod a-x '{}' ';'
find . -type f -iname '*.cpp' -exec chmod a-x '{}' ';'

%build
export CFLAGS="$RPM_OPT_FLAGS"
export CXXFLAGS="$RPM_OPT_FLAGS -std=gnu++98 -Wno-c++11-compat"
%configure --enable-fw-mgr
%make_build

%install
make DESTDIR=%{buildroot} install
# Remove the devel files that we don't ship
rm -fr %{buildroot}%{_includedir}
find %{buildroot} -type f -name '*.la' -delete
find %{buildroot} -type f -name libmtcr_ul.a -delete

%files
%doc README
%_bindir/*
%{_sysconfdir}/mstflint
%{_libdir}/mstflint

%{_datadir}/mstflint
%{_mandir}/man1/*

%changelog
* Sun May  6 2018 Honggang Li <honli@redhat.com> - 4.9.0-3
- Rebase to latest upstream release v4.9.0-3
- Resolves: bz1541740

* Tue Apr 17 2018 Honggang Li <honli@redhat.com> - 4.9.0-1
- Rebase to latest upstream release v4.9.0-1
- Resolves: bz1541740, bz1541489

* Thu Dec  7 2017 Honggang Li <honli@redhat.com> - 4.8.0-3
- Fixes mstvpd for mlx5 devices
- Resolves: bz1515993

* Sun Nov 12 2017 Honggang Li <honli@redhat.com> - 4.8.0-2
- Remove redundant file from mstflint
- Resolves: bz1512368

* Wed Nov  1 2017 Honggang Li <honli@redhat.com> - 4.8.0-1
- Rebase to upstream latest release 4.8.0
- Resolves: bz1456545

* Fri Oct  6 2017 Honggang Li <honli@redhat.com> - 4.7.0-1
- Rebase to upstream latest release 4.7.0
- Resolves: bz1456545

* Tue Mar  7 2017 Honggang Li <honli@redhat.com> - 4.6.0-2
- Fix manpage issues reported by lexgrog.
- Resolves: bz948474

* Mon Feb 27 2017 Honggang Li <honli@redhat.com> - 4.6.0-1
- Rebase to latest upstream from github.
- Add man pages.
- Resolves: bz948474, bz1416697

* Wed Apr 20 2016 Honggang Li <honli@redhat.com> - 4.3.0-1.49.g9b9af70.1
- Rebase to latest upstream version 4.3.0-1.49.g9b9af70.
- Spec file cleanup.
- Related: bz1277500

* Mon Jun 22 2015 Michal Schmidt <mschmidt@redhat.com> - 4.0.1-1
- Update to latest upstream release.
- Related: bz1164542

* Fri Oct 17 2014 Doug Ledford <dledford@redhat.com> - 3.7.1-1
- Update to latest upstream release for added arch support
- Related: bz1055716

* Sat Mar 01 2014 Doug Ledford <dledford@redhat.com> - 3.5.0-1
- Update to latest release for ConnectIB fixes
- Resolves: bz1060514

* Thu Jan 23 2014 Doug Ledford <dledford@redhat.com> - 3.0-0.7.g6961daa.2
- Fix for build on arm arches
- Resolves: bz1055716

* Fri Dec 27 2013 Daniel Mach <dmach@redhat.com> - 3.0-0.7.g6961daa.1
- Mass rebuild 2013-12-27

* Fri Aug 16 2013 Doug Ledford <dledford@redhat.com> - 3.0-0.6.g6961daa.1
- Update to latest upstream version, which resovles some licensing issues
  on some of the source files

* Fri Aug 09 2013 Doug Ledford <dledford@redhat.com> - 3.0-0.5.gff93670.1
- Update to latest upstream version, which include ConnectIB support

* Sat Aug 03 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.4-10
- Rebuilt for https://fedoraproject.org/wiki/Fedora_20_Mass_Rebuild

* Thu Feb 14 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.4-9
- Rebuilt for https://fedoraproject.org/wiki/Fedora_19_Mass_Rebuild

* Fri Jul 20 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.4-8
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Fri Jan 13 2012 Doug Ledford <dledford@redhat.com> - 1.4-7
- The upstream tarball as provided is broken.  Clean up the tarball so
  the package builds properly

* Fri Jan 06 2012 Doug Ledford <dledford@redhat.com> - 1.4-6
- Initial import into Fedora

* Wed Oct 26 2011 Doug Ledford <dledford@redhat.com> - 1.4-5.el6
- Update to a version that will support the latest Mellanox CX3 hardware
- Resolves: bz748244

* Mon Aug 08 2011 Doug Ledford <dledford@redhat.com> - 1.4-4.el6
- Fix a bug in mmio space unmapping
- Resolves: bz729061
- Related: bz725016

* Fri Feb 19 2010 Doug Ledford <dledford@redhat.com> - 1.4-3.el6
- Don't include mtcr.h as we don't really expect anything to need Mellanox
  card register definitions except this program, and we already have the
  file.
- Change to ExcludeArch instead of ExclusiveArch so we build in all the right
  places.
- Related: bz543948

* Mon Jan 25 2010 Doug Ledford <dledford@redhat.com> - 1.4-2.el6
- Update to tarball from URL instead of from OFED
- Minor tweaks for pkgwrangler import
- Related: bz543948

* Sat Apr 18 2009 Doug Ledford <dledford@redhat.com> - 1.4-1.el5
- Update to ofed 1.4.1-rc3 version
- Related: bz459652

* Tue Apr 01 2008 Doug Ledford <dledford@redhat.com> - 1.3-1
- Update to OFED 1.3 final bits
- Related: bz428197

* Sun Jan 27 2008 Doug Ledford <dledford@redhat.com> - 1.2-2
- Obsolete the old openib-mstflint package

* Fri Jan 25 2008 Doug Ledford <dledford@redhat.com> - 1.2-1
- Initial import into CVS
- Related: bz428197

* Thu Jul 19 2007 - Vladimir Sokolovsky vlad@mellanox.co.il
- Initial Package, Version 1.2
