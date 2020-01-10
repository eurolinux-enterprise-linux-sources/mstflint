Summary: Mellanox firmware burning application
Name: mstflint
Version: 1.4
Release: 1.18.g1adcfbf
License: GPL/BSD
Url: http://openib.org/
Group: System Environment/Base
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}
Source: http://www.openfabrics.org/downloads/mstflint-1.4-1.18.g1adcfbf.tar.gz
ExclusiveArch: i386 i486 i586 i686 x86_64 ia64 ppc ppc64
BuildRequires: zlib-devel

%description
This package contains a tool for burning updated firmware on to
Mellanox manufactured InfiniBand adapters.

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
%{_bindir}/mstvpd
%{_bindir}/mstmcra
%{_bindir}/hca_self_test.ofed
%{_includedir}/mtcr_ul/mtcr.h

%changelog
* Thu Dec  4 2008 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   Added hca_self_test.ofed installation
   
* Fri Dec 23 2007 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   Added mtcr.h installation
   
* Fri Dec 07 2007 Ira Weiny <weiny2@llnl.gov> 1.0.0
   initial creation

