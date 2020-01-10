Name:		mstflint
Summary:	Mellanox firmware burning tool
Version:	3.0
Release:	0.6.g6961daa.1%{?dist}
License:	GPLv2+ or BSD
Group:		Applications/System
Source:		http://www.openfabrics.org/downloads/%{name}/%{name}-%{version}-0.6.g6961daa.tar.gz
Url:		http://www.openfabrics.org
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:	libstdc++-devel, zlib-devel
Obsoletes:	openib-mstflint <= 1.4 openib-tvflash <= 0.9.2 tvflash <= 0.9.0
ExcludeArch:	s390 s390x

%description
This package contains a burning tool for Mellanox manufactured HCA cards.
It also provides access to the relevant source code.

%prep
%setup -q

%build
export CFLAGS="$RPM_OPT_FLAGS"
%configure
make

%install
rm -rf %{buildroot}
make DESTDIR=%{buildroot} install
# Remove the devel files that we don't ship
rm -fr %{buildroot}%{_includedir}
rm -fr %{buildroot}%{_datadir}

%clean
rm -rf %{buildroot}

%files
%defattr(-, root, root)
%doc README
%_bindir/*

%changelog
* Fri Aug 16 2013 Doug Ledford <dledford@redhat.com> - 3.0-0.6.g6961daa.1
- Update to newer tarball that resolves licensing issues with the last
  tarball
- Related: bz818183

* Fri Aug 09 2013 Doug Ledford <dledford@redhat.com> - 3.0-0.5.gff93670.1
- Update to latest upstream version, which includes ConnectIB support
- Resolves: bz818183

* Tue Jan 31 2012 Doug Ledford <dledford@redhat.com> - 1.4-6
- Turns out that the previous tarball was full of cruft that upstream should
  have never let make its way into the tarball.  I had to clean the tarball
  out in order to get the package to build properly.
- Related: bz739138

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
