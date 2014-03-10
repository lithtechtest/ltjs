/****************************************************************************
 * 
 *  $Id: rmaauth.h,v 1.18 1999/01/29 18:32:10 hboone Exp $
 *  
 *  Copyright (C) 1995-1999 RealNetworks, Inc. All rights reserved.
 *
 *  http://www.real.com/devzone
 *
 *  This program contains proprietary 
 *  information of Progressive Networks, Inc, and is licensed
 *  subject to restrictions on use and distribution.
 *
 *  Authentication and password interfaces. 
 *
 */

#ifndef _RMAAUTH_H_
#define _RMAAUTH_H_

/*
 * Forward declarations of some interfaces defined or used here-in.
 */
typedef _INTERFACE  IRMAAuthenticator		    IRMAAuthenticator;
typedef _INTERFACE  IRMAAuthenticatorResponse	    IRMAAuthenticatorResponse;
typedef _INTERFACE  IRMAAuthenticatorRequest	    IRMAAuthenticatorRequest;
typedef _INTERFACE  IRMAPassword		    IRMAPassword;
typedef _INTERFACE  IRMAAuthenticationManagerResponse IRMAAuthenticationManagerResponse;
typedef _INTERFACE  IRMAValues			    IRMAValues;
typedef _INTERFACE  IRMABuffer			    IRMABuffer;

/****************************************************************************
 * 
 *  Interface:
 * 
 *      IRMAAuthenticator
 * 
 *  Purpose:
 * 
 *      Provide a means of authenticating users.
 *
 *  IID_IRMAAuthenticator:
 * 
 *      {00001800-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IRMAAuthenticator, 0x00001800, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			0xa0, 0x24, 0x40, 0x6d, 0x59);

#define CLSID_IRMAAuthenticator IID_IRMAAuthenticator

#undef  INTERFACE
#define INTERFACE IRMAAuthenticator

DECLARE_INTERFACE_(IRMAAuthenticator, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;

    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /*
     * InitAuthenticator is called by the creator of the Authenticator
     * object in order to pass it an IRMAAuthenticatorRequest object,
     * usually implemented by the creator itself.
     */
    STDMETHOD(InitAuthenticator) (THIS_ 
				  IRMAAuthenticatorRequest* pRequest) PURE;
    /*
     * Authenticate is called by a file object (and others??)
     * when it wants to ask the creator, presumably an FS Manager,
     * for authorization to open it's file.
     *
     * Authenticate will call IRMAAuthenticateResponse::AuthenticateDone
     * when done with PNR_OK or an error.
     *
     * File objects will presumably perform the Authenticate response as
     * part of their Init() call, and not call InitDone until they receive
     * a response one way or the other.
     */
    STDMETHOD(Authenticate) (THIS_
			     IRMAValues* pValues,
			     IRMAAuthenticatorResponse* pResponse) PURE;

    /* GenerateAuthRequest is called by the creator of this object
     * when they want to send an authentication request to someone.
     */
    STDMETHOD(GenerateAuthRequest) (THIS_
				    UINT32 authType,
				    REF(IRMAValues*) pValues) PURE;
    /*
     * AuthValuesReady is called by IRMAAuthenticatorRequest when it
     * is ready to respond to a GetAuthValues request.
     */
    STDMETHOD(AuthValuesReady) (THIS_ 
				PN_RESULT result,
				IRMAValues* pValues) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IRMAAuthenticatorResponse
 * 
 *  Purpose:
 *
 *      Response object for the Authenticator class.
 * 
 *  IID_IRMAAuthenticatorResponse:
 * 
 *      {00001801-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IRMAAuthenticatorResponse, 0x00001801, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE IRMAAuthenticatorResponse

DECLARE_INTERFACE_(IRMAAuthenticatorResponse, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;

    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* AuthenticateDone is called by an IRMAAuthenticator when it has
     * finished it's authorization steps.  If the result is PNR_OK,
     * then the values contain authorization information as generated by
     * IRMAPassword.
     */
    STDMETHOD(AuthenticateDone) (THIS_ PN_RESULT result,
				IRMAValues* pAuthResponseValues) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IRMAAuthenticatorRequest
 * 
 *  Purpose:
 *
 *      Request object for the Authenticator class.
 * 
 *  IID_IRMAAuthenticatorRequest:
 * 
 *      {00001802-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IRMAAuthenticatorRequest, 0x00001802, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE IRMAAuthenticatorRequest

DECLARE_INTERFACE_(IRMAAuthenticatorRequest, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;

    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* GetAuthValues is called by the Authenticator object when it
     * needs to know the authorization info for this transaction.
     *
     * This object should call AuthValuesReady when ready.
     */
    STDMETHOD(GetAuthValues) (THIS_ IRMAValues* pOrigValues) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IRMAPassword
 * 
 *  Purpose:
 * 
 *      Provides a general password facility for storing of passwords in
 *	an encrypted form and a facility for verifying passwords securely
 *	over the network.
 * 
 *  IID_IRMAPassword:
 * 
 *      {00001700-0901-11d1-8B06-00A024406D59}
 * 
 */

#define PN_AUTH_BASIC	1
#define PN_AUTH_DIGEST	2
#define PN_AUTH_RN5	3
#define PN_AUTH_NTLM	4

DEFINE_GUID(IID_IRMAPassword, 0x00001700, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE IRMAPassword

DECLARE_INTERFACE_(IRMAPassword, IUnknown)
{
    /*
     *  IUnknown methods
     */
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;

    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /*
     *  IRMAPassword methods
     */

    STDMETHOD(Crypt) (THIS_ IRMAValues* pAuthentication) PURE;
    STDMETHOD(Verify) (THIS_ IRMAValues* pAuth1, IRMAValues* pAuth2) PURE;

    STDMETHOD(AsString) (THIS_ IRMAValues* pAuth, REF(IRMABuffer*) pBuffer) PURE;
    STDMETHOD(AsValues) (THIS_ const char* str, IRMAValues* pValues) PURE;

    /*
     * CreateBuffer is provided for the convenince of external users,
     * who would otherwise have to get a context and common class factory
     * just to create IRMABuffers.  This method can be used instead, but
     * is not advisable if other means are available.
     */
    STDMETHOD(CreateBuffer) (THIS_ REF(IRMABuffer*) pBuffer) PURE;

    /*
     * Ditto for CreateValues
     */
    STDMETHOD(CreateValues) (THIS_ REF(IRMAValues*) pValues) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IRMAAuthenticationManager
 * 
 *  Purpose:
 * 
 *      Provide a means of authenticating users.
 *
 *  IID_IRMAAuthenticator:
 * 
 *      {00001a00-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IRMAAuthenticationManager, 0x00001a00, 0x901, 0x11d1,
	    0x8b, 0x6, 0x0, 0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE IRMAAuthenticationManager

DECLARE_INTERFACE_(IRMAAuthenticationManager, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;
    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;
    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* HandleAuthenticationRequest is called when the core wants us to get
     * a username and password.
     */
    STDMETHOD(HandleAuthenticationRequest) (
	THIS_ IRMAAuthenticationManagerResponse* pResponse) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IRMAAuthenticationManagerResponse
 * 
 *  Purpose:
 * 
 *      Response object for IRMAAuthenticationManager.
 *
 *  IID_IRMAAuthenticator:
 * 
 *      {00001a01-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IRMAAuthenticationManagerResponse, 0x00001a01, 0x901, 0x11d1,
            0x8b, 0x6, 0x0, 0xa0, 0x24, 0x40, 0x6d, 0x59); 


#undef  INTERFACE
#define INTERFACE IRMAAuthenticationManagerResponse

DECLARE_INTERFACE_(IRMAAuthenticationManagerResponse, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;
    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;
    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* HandleAuthenticationRequest is called when the core wants us to get
     * a username and password.
     */
    STDMETHOD(AuthenticationRequestDone) (THIS_
					  PN_RESULT result,
					  const char* pUserName,
					  const char* pPassword) PURE;
};

#ifdef _MACINTOSH
#pragma export on
#endif

STDAPI CreatePassword(IUnknown** /* OUT */ ppIUnknown);

#ifdef _MACINTOSH
#pragma export off
#endif

#endif /* _RMAAUTH_H_ */
