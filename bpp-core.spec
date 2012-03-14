%define _basename bpp-core
%define _version 2.0.3
%define _release 1
%define _prefix /usr

URL: http://biopp.univ-montp2.fr/

Name: %{_basename}
Version: %{_version}
Release: %{_release}
License: CECILL-2.0
Vendor: The Bio++ Project
Source: http://biopp.univ-montp2.fr/repos/sources/%{_basename}-%{_version}.tar.gz
Summary: Bio++ Core library
Group: Development/Libraries/C and C++

BuildRoot: %{_builddir}/%{_basename}-root
BuildRequires: cmake >= 2.6.0
BuildRequires: gcc-c++ >= 4.0.0
AutoReq: yes
AutoProv: yes

%description
This library contains the core classes and utilitary functions of the Bio++ project.

%package -n libbpp-core2
Summary: Bio++ Core library
Group: Development/Libraries/C and C++

%description -n libbpp-core2
This library contains the core classes and utilitary functions of the Bio++ project.

%package -n libbpp-core-devel
Summary: Libraries, includes to develop applications with %{_basename}
Group: Development/Libraries/C and C++
Requires: %{_basename} = %{_version}

%description -n libbpp-core-devel
The %{_basename}-devel package contains the header files and static libraries for
building applications which use %{_basename}.

%prep
%setup -q

%build
CFLAGS="$RPM_OPT_FLAGS"
CMAKE_FLAGS="-DCMAKE_INSTALL_PREFIX=%{_prefix} -DBUILD_TESTING=OFF"
if [ %{_lib} == 'lib64' ] ; then
  CMAKE_FLAGS="$CMAKE_FLAGS -DLIB_SUFFIX=64"
fi
cmake $CMAKE_FLAGS .
make

%install
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%post -n libbpp-core2 -p /sbin/ldconfig

%postun -n libbpp-core2 -p /sbin/ldconfig

%files -n libbpp-core2
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%{_prefix}/%{_lib}/lib*.so.*

%files -n libbpp-core-devel
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%{_prefix}/%{_lib}/lib*.so
%{_prefix}/%{_lib}/lib*.a
%{_prefix}/include/*

%changelog
* Thu Feb 09 2012 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.3-1
- More matrix and text tools.
* Thu Jun 09 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.2-1
- New MVA classes + more numerical tools.
* Mon Feb 28 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.1-1
- Fixed missing RColorSet file.
* Mon Feb 07 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.0-1
- Initial package.
