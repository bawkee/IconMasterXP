================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : IconMasterXP Project Overview
===============================================================================

The application wizard has created this IconMasterXP application for 
you.  This application not only demonstrates the basics of using the Microsoft 
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your IconMasterXP application.

IconMasterXP.vcproj
    This is the main project file for VC++ projects generated using an application wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    application wizard.

IconMasterXP.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CIconMasterXPApp application class.

IconMasterXP.cpp
    This is the main application source file that contains the application
    class CIconMasterXPApp.

IconMasterXP.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\IconMasterXP.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file IconMasterXP.rc.

res\IconMasterXP.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++. You should place all resources not editable by
    the resource editor in this file.
/////////////////////////////////////////////////////////////////////////////

For the main frame window:
    Windows Explorer Style: The project will include a Windows Explorer-like
    interface, with two frames.
MWnd.h, MWnd.cpp
    These files contain the frame class CMWnd, which is derived from
    CFrameWnd and controls all SDI frame features.
IconEditor.h, IconEditor.cpp
    These files contain the left frame class CIconEditor, which is derived from
    CTreeView.
res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMWnd
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in IconMasterXP.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

The application wizard creates one document type and one view:

Doc.h, Doc.cpp - the document
    These files contain your CDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CDoc::Serialize).
IconView.h, IconView.cpp - the view of the document
    These files contain your CIconView class.
    CIconView objects are used to view CDoc objects.
/////////////////////////////////////////////////////////////////////////////

Other Features:

ActiveX Controls
    The application includes support to use ActiveX controls.

Split Window
    The application wizard has added support for splitter windows for your application documents.
/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named IconMasterXP.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

IconMasterXP.manifest
	Application manifest files are used by Windows XP to describe an applications 
	dependency on specific versions of Side-by-Side assemblies. The loader uses this 
	information to load the appropriate assembly from the assembly cache or private 
	from the application. The Application manifest  maybe included for redistribution 
	as an external .manifest file that is installed in the same folder as the application 
	executable or it may be included in the executable in the form of a resource. 
/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is in a 
language other than the operating system's current language, you will need 
to copy the corresponding localized resources MFC70XXX.DLL from the Microsoft
Visual C++ CD-ROM under the Win\System directory to your computer's system or 
system32 directory, and rename it to be MFCLOC.DLL.  ("XXX" stands for the 
language abbreviation.  For example, MFC70DEU.DLL contains resources 
translated to German.)  If you don't do this, some of the UI elements of 
your application will remain in the language of the operating system.

/////////////////////////////////////////////////////////////////////////////


Export notes:

Ovde sam stao, CxImage ne zna za gresku u dekodiranju maske, transparenta boja mora uvek
biti prva u paleti, ili (ne secam se najbolje) - crna.
Najbolje je modifikovati kod u biblioteci da ili premesti boju ili zameni crnom, ili tako
nesto, pogledaj kako stari icon master to radi.
Naime, postoji boja koja se prikazuje na mesto transparente U ODREDJENIM momentima u odredjenim
programima, kod CxImage to je ljubicasta najcesce, u GMG to je svetlo plava, problem je u tome
sto ja za razliku od gmg-a nemam pojma kako da nateram programe da otvaraju moju tako reci "custom"
transparenciju, odnosno masku....
Nova zapazanja :P -->
Izgleda da gmg bira opcije:
Postavlja odredjenu fisknu boju kao transparentnu, ignorisuci predhodnu (ako recimo neki treci program
koristi plavu, ovaj ce je je ukloniti, i postavice tamno crvenu kao trecu boju u paleti).
Ako ima dovoljno mesta u paleti, menja postojecu crnu, za recimo samo jedan broj, i postavlja pravu
crnu boju na mesto transparentne, tako je i sacuvava menjajuci pri tome metod koji je predhodno koriscen
od strane drugog programa... Mislim da je to i icon master radio.
Uzima belu boju, isti slucaj kao i sa crnom, samo sto i bela prolazi ako je prva u paleti...
Jos zapazanja >
Ljubicasta izgleda potice od mspainta, i gmg 4bitne ikone pokriva tom bojom.....
Takodje, izgleda da bira bilo koju slobodnu boju kao transparentnu, samo dok je TRECA po redu. Cudno...
Postaje sjebano, ovaj program ima relativno delikatan sistem za biranje transparentne boje :/
Okej, ovo je stvarno cudno, najbolje je napisati poseban kod samo za konverziju jebenih 4-bitnih
ikona i manjih, ostale se daju lako srediti...
Furthermore, windows explorer npr. invertuje AND masku, tako da se vidi invertovana transparentna
boja, kewl eh? To je ona ljubicasta boja, dakle invertovana tamno zelena........

--------------
Problem resen, resenje je da se koriste 2 crne boje, jedna je prava, druga je lazna, ali 
dva razlicita indeksa = dve razlicite boje, tako da nema nikakvih neslaganja. Ovo se radi
SAMO prilikom eksportovanja, i pozeljno je vratiti stare slike posto se konverzija zavrsi.
Treba srediti kod u biblioteci, malo je neuredan posle tih izmena. Ispod je kod koji nalazi
transparentnu boju u paleti i pretvara je u nulu, koja je validna u svim programima kao
transparentna boja.

Malo sam svrljao po internetu za FOLDER SELECT dialog, nasao sam super klasu, ali treba
joj 3 sekunde da popuni listu, sto je previse pa cu nastaviti da trazim...

Uradi pitanje, da li da zamenim postojecu ikonu prilikom eksporta. Takodje preventiraj eksport ikona
sa invalidnim velicinama..... ako je -> (x!=y)
