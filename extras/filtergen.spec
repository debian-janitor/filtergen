# $Id: filtergen.spec,v 1.5 2002/09/12 10:03:01 matthew Exp $
Summary: Firewall rule generator
Name: filtergen
Version: 0.10
Release: 1
License: GPL
Group: Applications/System
Source: http://hairy.beasts.org/filter/filtergen-%{version}.tar.gz
URL: http://hairy.beasts.org/filter/
Buildroot: %{_tmppath}/%{name}-root
BuildPrereq: rpm-build gcc flex make
Packager: Wil Cooley <wcooley@nakedape.cc>
Vendor: Naked Ape Consulting <http://nakedape.cc>

%description
This tool is for generating packet filtering rules from a fairly
high- level description language.  It doesn't support all of the
whizz-bang features of the latest and greatest packet filters,
but supports a useful subset.


%prep
%setup -q -n filtergen-%{version}

%build
make CFLAGS="${RPM_OPT_FLAGS}" LDFLAGS="-lfl"

%install
rm -rf $RPM_BUILD_ROOT
make PREFIX=${RPM_BUILD_ROOT}/usr BINDIR=${RPM_BUILD_ROOT}/sbin install
install -d ${RPM_BUILD_ROOT}/etc/init.d
install -m755 extras/filter.init ${RPM_BUILD_ROOT}/etc/init.d/filter
install -d ${RPM_BUILD_ROOT}/etc/filter
install extras/etc-filter-Makefile ${RPM_BUILD_ROOT}/etc/filter/Makefile

%post
/sbin/chkconfig --add filter
/sbin/chkconfig filter off

%preun
/sbin/service filter accept
/sbin/chkconfig --del filter

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/sbin/filtergen
/etc/init.d/filter
/etc/filter/
%{_mandir}/*
%doc HISTORY HONESTY README TODO INSTALL tests/host-sample.filter tests/router-sample.filter tests/proxy-fw-sample.filter

%changelog
* Mon Sep  2 2002 Matthew Kirkwood <matthew@hairy.beasts.org> 0.10-1
- Add new sample and documentation stuff

* Sun Aug 18 2002 Wil Cooley <wcooley@nakedape.cc> 0.8-1
- Initial RPM creation