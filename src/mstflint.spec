Summary: Mellanox firmware burning application
Name: mstflint
Version: 3.0
Release: 0.6.g6961daa
License: GPL/BSD
Url: http://openfabrics.org
Group: System Environment/Base
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}
Source: http://www.openfabrics.org/downloads/mstflint-3.0-0.6.g6961daa.tar.gz
ExclusiveArch: i386 i486 i586 i686 x86_64 ia64 ppc ppc64
BuildRequires: zlib-devel

%description
This package contains firmware update tool, vpd dump and register dump tools
for network adapters based on Mellanox Technologies chips.

%prep
%setup -q

%build
%configure
make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=${RPM_BUILD_ROOT} install
# remove unpackaged files from the buildroot
rm -f $RPM_BUILD_ROOT%{_libdir}/*.la

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_bindir}/mstmread
%{_bindir}/mstmwrite
%{_bindir}/mstflint
%{_bindir}/mstregdump
%{_bindir}/mstmtserver
%{_bindir}/mstvpd
%{_bindir}/mstmcra
%{_bindir}/hca_self_test.ofed
%{_includedir}/mtcr_ul/mtcr.h
%{_datadir}/mstflint

%changelog

* Wed Mar 20 2013 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   MFT 3.0.0

* Thu Dec  4 2008 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   Added hca_self_test.ofed installation
   
* Fri Dec 23 2007 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   Added mtcr.h installation
   
* Fri Dec 07 2007 Ira Weiny <weiny2@llnl.gov> 1.0.0
   initial creation

