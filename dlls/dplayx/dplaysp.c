/* This contains the implementation of the interface Service
 * Providers require to communicate with Direct Play
 *
 * Copyright 2000 Peter Hunnisett
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

#include <string.h>
#include "winerror.h"
#include "wine/debug.h"

#include "wine/dplaysp.h"
#include "dplay_global.h"
#include "name_server.h"
#include "dplayx_messages.h"

#include "dplayx_global.h" /* FIXME: For global hack */

/* FIXME: Need to add interface locking inside procedures */

WINE_DEFAULT_DEBUG_CHANNEL(dplay);

typedef struct IDirectPlaySPImpl
{
  IDirectPlaySP IDirectPlaySP_iface;
  LONG ref;
  void *remote_data;
  DWORD remote_data_size;
  void *local_data;
  DWORD local_data_size;
  IDirectPlayImpl *dplay; /* FIXME: This should perhaps be iface not impl */
} IDirectPlaySPImpl;

/* This structure is passed to the DP object for safe keeping */
typedef struct tagDP_SPPLAYERDATA
{
  LPVOID lpPlayerLocalData;
  DWORD  dwPlayerLocalDataSize;

  LPVOID lpPlayerRemoteData;
  DWORD  dwPlayerRemoteDataSize;
} DP_SPPLAYERDATA, *LPDP_SPPLAYERDATA;


static inline IDirectPlaySPImpl *impl_from_IDirectPlaySP( IDirectPlaySP *iface )
{
  return CONTAINING_RECORD( iface, IDirectPlaySPImpl, IDirectPlaySP_iface );
}

static HRESULT WINAPI IDirectPlaySPImpl_QueryInterface( IDirectPlaySP *iface, REFIID riid,
        void **ppv )
{
  TRACE("(%p)->(%s,%p)\n", iface, debugstr_guid( riid ), ppv );

  if ( IsEqualGUID( &IID_IUnknown, riid ) || IsEqualGUID( &IID_IDirectPlaySP, riid ) )
  {
    *ppv = iface;
    IDirectPlaySP_AddRef( iface );
    return S_OK;
  }

  FIXME( "Unsupported interface %s\n", debugstr_guid( riid ) );
  *ppv = NULL;
  return E_NOINTERFACE;
}

static ULONG WINAPI IDirectPlaySPImpl_AddRef( IDirectPlaySP *iface )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );
  ULONG ref = InterlockedIncrement( &This->ref );

  TRACE( "(%p) ref=%d\n", This, ref );

  return ref;
}

static ULONG WINAPI IDirectPlaySPImpl_Release( IDirectPlaySP *iface )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );
  ULONG ref = InterlockedDecrement( &This->ref );

  TRACE( "(%p) ref=%d\n", This, ref );

  if( !ref )
  {
    HeapFree( GetProcessHeap(), 0, This->remote_data );
    HeapFree( GetProcessHeap(), 0, This->local_data );
    HeapFree( GetProcessHeap(), 0, This );
  }

  return ref;
}

static HRESULT WINAPI IDirectPlaySPImpl_AddMRUEntry( IDirectPlaySP *iface, LPCWSTR lpSection,
        LPCWSTR lpKey, const void *lpData, DWORD dwDataSize, DWORD dwMaxEntries )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );

  /* Should be able to call the comctl32 undocumented MRU routines.
     I suspect that the interface works appropriately */
  FIXME( "(%p)->(%p,%p%p,0x%08x,0x%08x): stub\n",
         This, lpSection, lpKey, lpData, dwDataSize, dwMaxEntries );

  return DP_OK;
}

static HRESULT WINAPI IDirectPlaySPImpl_CreateAddress( IDirectPlaySP *iface, REFGUID guidSP,
        REFGUID guidDataType, const void *lpData, DWORD dwDataSize, void *lpAddress,
        DWORD *lpdwAddressSize )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );

  FIXME( "(%p)->(%s,%s,%p,0x%08x,%p,%p): stub\n",
         This, debugstr_guid(guidSP), debugstr_guid(guidDataType),
         lpData, dwDataSize, lpAddress, lpdwAddressSize );

  return DP_OK;
}

static HRESULT WINAPI IDirectPlaySPImpl_EnumAddress( IDirectPlaySP *iface,
        LPDPENUMADDRESSCALLBACK lpEnumAddressCallback, const void *lpAddress, DWORD dwAddressSize,
        void *lpContext )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );

  TRACE( "(%p)->(%p,%p,0x%08x,%p)\n",
         This, lpEnumAddressCallback, lpAddress, dwAddressSize, lpContext );

  DPL_EnumAddress( lpEnumAddressCallback, lpAddress, dwAddressSize, lpContext );

  return DP_OK;
}

static HRESULT WINAPI IDirectPlaySPImpl_EnumMRUEntries( IDirectPlaySP *iface, LPCWSTR lpSection,
        LPCWSTR lpKey, LPENUMMRUCALLBACK lpEnumMRUCallback, void *lpContext )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );

  /* Should be able to call the comctl32 undocumented MRU routines.
     I suspect that the interface works appropriately */
  FIXME( "(%p)->(%p,%p,%p,%p): stub\n",
         This, lpSection, lpKey, lpEnumMRUCallback, lpContext );

  return DP_OK;
}

static HRESULT WINAPI IDirectPlaySPImpl_GetPlayerFlags( IDirectPlaySP *iface, DPID idPlayer,
        DWORD *lpdwPlayerFlags )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );

  FIXME( "(%p)->(0x%08x,%p): stub\n",
         This, idPlayer, lpdwPlayerFlags );

  return DP_OK;
}

static HRESULT WINAPI IDirectPlaySPImpl_GetSPPlayerData( IDirectPlaySP *iface, DPID idPlayer,
        void **lplpData, DWORD *lpdwDataSize, DWORD dwFlags )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );
  HRESULT hr;
  LPDP_SPPLAYERDATA lpPlayerData;

  TRACE( "(%p)->(0x%08x,%p,%p,0x%08x)\n",
         This, idPlayer, lplpData, lpdwDataSize, dwFlags );

  hr = DP_GetSPPlayerData( This->dplay, idPlayer, (void**)&lpPlayerData );

  if( FAILED(hr) )
  {
    ERR( "Couldn't get player data: %s\n", DPLAYX_HresultToString(hr) );
    return hr;
  }

  if( dwFlags == DPSET_LOCAL )
  {
    *lplpData     = lpPlayerData->lpPlayerLocalData;
    *lpdwDataSize = lpPlayerData->dwPlayerLocalDataSize;
  }
  else if( dwFlags == DPSET_REMOTE )
  {
    *lplpData     = lpPlayerData->lpPlayerRemoteData;
    *lpdwDataSize = lpPlayerData->dwPlayerRemoteDataSize;
  }

  return DP_OK;
}

static HRESULT WINAPI IDirectPlaySPImpl_HandleMessage( IDirectPlaySP *iface, void *lpMessageBody,
        DWORD dwMessageBodySize, void *lpMessageHeader )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );
  LPDPSP_MSG_ENVELOPE lpMsg = lpMessageBody;
  DPSP_REPLYDATA data;
  HRESULT hr;

  TRACE( "(%p)->(%p,0x%08x,%p)\n",
         This, lpMessageBody, dwMessageBodySize, lpMessageHeader );

  TRACE( "Incoming message has envelope of 0x%08x, 0x%x, %u\n",
         lpMsg->dwMagic, lpMsg->wCommandId, lpMsg->wVersion );

  if( lpMsg->dwMagic != DPMSG_SIGNATURE )
  {
    ERR( "Unknown magic 0x%08x!\n", lpMsg->dwMagic );
    return DPERR_GENERIC;
  }

  /* Pass everything else to Direct Play */
  data.lpMessage     = NULL;
  data.dwMessageSize = 0;

  /* Pass this message to the dplay interface to handle */
  hr = DP_HandleMessage( This->dplay, lpMessageBody, dwMessageBodySize, lpMessageHeader,
                         lpMsg->wCommandId, lpMsg->wVersion, &data.lpMessage, &data.dwMessageSize );

  if( FAILED(hr) )
  {
    ERR( "Command processing failed %s\n", DPLAYX_HresultToString(hr) );
  }

  /* Do we want a reply? */
  if( data.lpMessage != NULL )
  {
    data.lpSPMessageHeader = lpMessageHeader;
    data.idNameServer      = 0;
    data.lpISP             = iface;

    hr = This->dplay->dp2->spData.lpCB->Reply( &data );

    if( FAILED(hr) )
    {
      ERR( "Reply failed %s\n", DPLAYX_HresultToString(hr) );
    }
  }

  return hr;
}

static HRESULT WINAPI IDirectPlaySPImpl_SetSPPlayerData( IDirectPlaySP *iface, DPID idPlayer,
        void *lpData, DWORD dwDataSize, DWORD dwFlags )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );
  HRESULT           hr;
  LPDP_SPPLAYERDATA lpPlayerEntry;
  LPVOID            lpPlayerData;

  TRACE( "(%p)->(0x%08x,%p,0x%08x,0x%08x)\n", This, idPlayer, lpData, dwDataSize, dwFlags );

  hr = DP_GetSPPlayerData( This->dplay, idPlayer, (void**)&lpPlayerEntry );
  if( FAILED(hr) )
  {
    /* Player must not exist */
    return DPERR_INVALIDPLAYER;
  }

  lpPlayerData = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwDataSize );
  CopyMemory( lpPlayerData, lpData, dwDataSize );

  /* If we have data already allocated, free it and replace it */
  if( dwFlags == DPSET_LOCAL )
  {
    HeapFree( GetProcessHeap(), 0, lpPlayerEntry->lpPlayerLocalData );
    lpPlayerEntry->lpPlayerLocalData = lpPlayerData;
    lpPlayerEntry->dwPlayerLocalDataSize = dwDataSize;
  }
  else if( dwFlags == DPSET_REMOTE )
  {
    HeapFree( GetProcessHeap(), 0, lpPlayerEntry->lpPlayerRemoteData );
    lpPlayerEntry->lpPlayerRemoteData = lpPlayerData;
    lpPlayerEntry->dwPlayerRemoteDataSize = dwDataSize;
  }

  hr = DP_SetSPPlayerData( This->dplay, idPlayer, lpPlayerEntry );

  return hr;
}

static HRESULT WINAPI IDirectPlaySPImpl_CreateCompoundAddress( IDirectPlaySP *iface,
        const DPCOMPOUNDADDRESSELEMENT *lpElements, DWORD dwElementCount, void *lpAddress,
        DWORD *lpdwAddressSize )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );

  FIXME( "(%p)->(%p,0x%08x,%p,%p): stub\n",
         This, lpElements, dwElementCount, lpAddress, lpdwAddressSize );

  return DP_OK;
}

static HRESULT WINAPI IDirectPlaySPImpl_GetSPData( IDirectPlaySP *iface, void **lplpData,
        DWORD *lpdwDataSize, DWORD dwFlags )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );

  TRACE( "(%p)->(%p,%p,0x%08x)\n", This, lplpData, lpdwDataSize, dwFlags );

  if( dwFlags == DPSET_REMOTE )
  {
    *lpdwDataSize = This->remote_data_size;
    *lplpData = This->remote_data;
  }
  else if( dwFlags == DPSET_LOCAL )
  {
    *lpdwDataSize = This->local_data_size;
    *lplpData = This->local_data;
  }

  return DP_OK;
}

static HRESULT WINAPI IDirectPlaySPImpl_SetSPData( IDirectPlaySP *iface, void *lpData,
        DWORD dwDataSize, DWORD dwFlags )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );
  LPVOID lpSpData;

  TRACE( "(%p)->(%p,0x%08x,0x%08x)\n", This, lpData, dwDataSize, dwFlags );

  lpSpData = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwDataSize );
  CopyMemory( lpSpData, lpData, dwDataSize );

  /* If we have data already allocated, free it and replace it */
  if( dwFlags == DPSET_REMOTE )
  {
    HeapFree( GetProcessHeap(), 0, This->remote_data );
    This->remote_data_size = dwDataSize;
    This->remote_data = lpSpData;
  }
  else if ( dwFlags == DPSET_LOCAL )
  {
    HeapFree( GetProcessHeap(), 0, This->local_data );
    This->local_data = lpSpData;
    This->local_data_size = dwDataSize;
  }

  return DP_OK;
}

static void WINAPI IDirectPlaySPImpl_SendComplete( IDirectPlaySP *iface, void *unknownA,
        DWORD unknownB )
{
  IDirectPlaySPImpl *This = impl_from_IDirectPlaySP( iface );

  FIXME( "(%p)->(%p,0x%08x): stub\n",
         This, unknownA, unknownB );
}

static const IDirectPlaySPVtbl directPlaySPVT =
{
  IDirectPlaySPImpl_QueryInterface,
  IDirectPlaySPImpl_AddRef,
  IDirectPlaySPImpl_Release,
  IDirectPlaySPImpl_AddMRUEntry,
  IDirectPlaySPImpl_CreateAddress,
  IDirectPlaySPImpl_EnumAddress,
  IDirectPlaySPImpl_EnumMRUEntries,
  IDirectPlaySPImpl_GetPlayerFlags,
  IDirectPlaySPImpl_GetSPPlayerData,
  IDirectPlaySPImpl_HandleMessage,
  IDirectPlaySPImpl_SetSPPlayerData,
  IDirectPlaySPImpl_CreateCompoundAddress,
  IDirectPlaySPImpl_GetSPData,
  IDirectPlaySPImpl_SetSPData,
  IDirectPlaySPImpl_SendComplete
};

HRESULT dplaysp_create( REFIID riid, void **ppv, IDirectPlayImpl *dp )
{
  IDirectPlaySPImpl *obj;
  HRESULT hr;

  TRACE( "(%s, %p)\n", debugstr_guid( riid ), ppv );

  *ppv = NULL;
  obj = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof( *obj ) );
  if ( !obj )
    return DPERR_OUTOFMEMORY;

  obj->IDirectPlaySP_iface.lpVtbl = &directPlaySPVT;
  obj->ref = 1;
  obj->dplay = dp;

  hr = IDirectPlaySP_QueryInterface( &obj->IDirectPlaySP_iface, riid, ppv );
  IDirectPlaySP_Release( &obj->IDirectPlaySP_iface );

  return hr;
}

/* DP external interfaces to call into DPSP interface */

/* Allocate the structure */
LPVOID DPSP_CreateSPPlayerData(void)
{
  TRACE( "Creating SPPlayer data struct\n" );
  return HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
                    sizeof( DP_SPPLAYERDATA ) );
}
