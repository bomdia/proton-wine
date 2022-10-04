/* WinRT Windows.Devices.Enumeration implementation
 *
 * Copyright 2022 Paul Gofman for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "private.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(mmdevapi);

struct device_access_information_statics
{
    IActivationFactory IActivationFactory_iface;
    IDeviceAccessInformationStatics IDeviceAccessInformationStatics_iface;
    LONG ref;
};

static inline struct device_access_information_statics *impl_from_IActivationFactory( IActivationFactory *iface )
{
    return CONTAINING_RECORD( iface, struct device_access_information_statics, IActivationFactory_iface );
}

static HRESULT WINAPI factory_QueryInterface( IActivationFactory *iface, REFIID iid, void **out )
{
    struct device_access_information_statics *impl = impl_from_IActivationFactory( iface );

    TRACE( "iface %p, iid %s, out %p stub!\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown ) ||
        IsEqualGUID( iid, &IID_IInspectable ) ||
        IsEqualGUID( iid, &IID_IActivationFactory ))
    {
        IInspectable_AddRef( (*out = &impl->IActivationFactory_iface) );
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_IDeviceAccessInformationStatics ))
    {
        IInspectable_AddRef( (*out = &impl->IDeviceAccessInformationStatics_iface) );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI factory_AddRef( IActivationFactory *iface )
{
    struct device_access_information_statics *impl = impl_from_IActivationFactory( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p, ref %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI factory_Release( IActivationFactory *iface )
{
    struct device_access_information_statics *impl = impl_from_IActivationFactory( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p, ref %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI factory_GetIids( IActivationFactory *iface, ULONG *iid_count, IID **iids )
{
    FIXME( "iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids );
    return E_NOTIMPL;
}

static HRESULT WINAPI factory_GetRuntimeClassName( IActivationFactory *iface, HSTRING *class_name )
{
    FIXME( "iface %p, class_name %p stub!\n", iface, class_name );
    return E_NOTIMPL;
}

static HRESULT WINAPI factory_GetTrustLevel( IActivationFactory *iface, TrustLevel *trust_level )
{
    FIXME( "iface %p, trust_level %p stub!\n", iface, trust_level );
    return E_NOTIMPL;
}

static HRESULT WINAPI factory_ActivateInstance( IActivationFactory *iface, IInspectable **instance )
{
    FIXME( "iface %p, instance %p stub!\n", iface, instance );
    return E_NOTIMPL;
}

static const struct IActivationFactoryVtbl factory_vtbl =
{
    factory_QueryInterface,
    factory_AddRef,
    factory_Release,
    /* IInspectable methods */
    factory_GetIids,
    factory_GetRuntimeClassName,
    factory_GetTrustLevel,
    /* IActivationFactory methods */
    factory_ActivateInstance,
};

DEFINE_IINSPECTABLE( statics, IDeviceAccessInformationStatics, struct device_access_information_statics, IActivationFactory_iface );

static HRESULT WINAPI statics_CreateFromId( IDeviceAccessInformationStatics *iface,
                                            HSTRING device_id, IDeviceAccessInformation **value)
{
    FIXME( "device_id %s, value %p stub.\n", debugstr_hstring( device_id ), value );

    return E_NOTIMPL;
}

static HRESULT WINAPI statics_CreateFromDeviceClassId( IDeviceAccessInformationStatics *iface,
                                                       GUID device_class_id, IDeviceAccessInformation **value)
{
    FIXME( "device_class_id %s, value %p stub.\n", debugstr_guid( &device_class_id ), value );

    return E_NOTIMPL;
}

static HRESULT WINAPI statics_CreateFromDeviceClass( IDeviceAccessInformationStatics *iface,
                                                     enum DeviceClass device_class, IDeviceAccessInformation **value)
{
    FIXME( "device_class %d, value %p stub.\n", device_class, value );

    return E_NOTIMPL;
}

static const struct IDeviceAccessInformationStaticsVtbl statics_vtbl =
{
    statics_QueryInterface,
    statics_AddRef,
    statics_Release,
    /* IInspectable methods */
    statics_GetIids,
    statics_GetRuntimeClassName,
    statics_GetTrustLevel,
    /* IDeviceAccessInformationStatics methods */
    statics_CreateFromId,
    statics_CreateFromDeviceClassId,
    statics_CreateFromDeviceClass,
};

static struct device_access_information_statics device_access_information_statics =
{
    {&factory_vtbl},
    {&statics_vtbl},
    1
};

IActivationFactory *device_access_factory = &device_access_information_statics.IActivationFactory_iface;
