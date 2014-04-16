//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

// XSecSurf.h: Collection of XSecs
// J.R Gloudemans
//
//////////////////////////////////////////////////////////////////////

#if !defined(XSECSURF__INCLUDED_)
#define XSECSURF__INCLUDED_

#include "XSec.h"
#include "XSecCurve.h"
#include "Airfoil.h"

#include <string>
#include <deque>

using std::string;
using std::deque;

class XSecSurf : public ParmContainer
{
public:

    XSecSurf();                                 // Default Constructor
    virtual ~XSecSurf();                        // Destructor

    XSec* FindXSec( string id );
    XSec* FindXSec( int index );
    int FindXSecIndex( string id );
    string GetXSecID( int index );
    void ChangeXSecID( string oldID, string newID );
    string AddXSec( int type );
    void CutXSec( int index );
    void CopyXSec( int index );
    void PasteXSec( int index );
    string InsertXSec( int type, int index );
    void ChangeXSecShape( int index, int type );

    void SetBasicOrientation( int pdir, int wdir, int wshift, bool flip )
    {
        m_PrincipalDir = pdir;
        m_WidthDir = wdir;
        if ( pdir == wdir )
        {
            printf("Error, principal and width directions identical.\n");
            assert( false );
        }
        m_WidthShift = wshift;
        m_FlipUD = flip;
    }

    void GetBasicTransformation( double w, Matrix4d &mat );

    bool GetFlipUD() { return m_FlipUD; }

    void SetXSecType( int xstype )
    {
        m_XSecType = xstype;
    }
    int GetXSecType( )
    {
        return m_XSecType;
    }

    virtual xmlNodePtr EncodeXml( xmlNodePtr & node );
    virtual xmlNodePtr DecodeXml( xmlNodePtr & node );

//  void SetParentID( string id );

    virtual void ParmChanged( Parm* parm_ptr, int type ) ;

    int NumXSec()
    {
        return m_XSecIDDeque.size();
    }

    virtual void AddLinkableParms( vector< string > & parm_vec, const string & link_container_id = string() );

    virtual string GetName();

protected:

    virtual void ChangeID( string id );

    XSec* CreateXSec( int type, int index );
    virtual void DeleteAllXSecs();

    vector< XSec* > m_XSecPtrVec;
    deque< string > m_XSecIDDeque;

    string m_SavedXSec;

    int m_XSecType;

    int m_PrincipalDir;
    int m_WidthDir;
    int m_WidthShift;
    bool m_FlipUD;

};

#endif // !defined(XSECSURF__INCLUDED_)