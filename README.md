# IconMasterXP
Is a Windows application for batch image conversion and processing, tailored for exporting Windows icons and other 'miniature' images (toolbar, web icons etc). Full source code is here along with the version of [CxImage](http://www.xdp.it/cximage/) library it is using for its core operations.

This used to be a *shareware* application but as of April 2018 it is free and open-source with a GPL license. It was originally developed back in 2004 and since then it was updated, enhanced and maintained. I have removed all the shareware-reated code and resources (nag screens, time limits, card processing, agreements and purchase instructions) and updated the official EULA.

**The official IconMasterXP website** is still the same, [www.iconmasterxp.com](http://iconmasterxp.com).

**If just you want to download the installation** then go to the [official download page](http://iconmasterxp.com/download).

## The Souce Code
The complete source code is available, along with the setup script, documentation source, dependant libraries and all the associated resources. 

It was originally written in 2004. in C++ by a 19 year old me and then updated many times as time went by which means that overral quality of the code is not exactly impeccable. Still though, it's surprisingly easy to follow it and understand what happens where - it strictly follows the old MFC document/view architecture so you can use Class Wizard (right click on class in Class View) to easily locate commands and events. 

You will need at least Visual Studio version 2010 to compile the main project. Documentation is available compiled in CHM already.

**The main project (IconMasterXP) is under GPL license which means that:**
* You are not allowed to rename the application or distribute it as your own or distribute any part of the application without the reference to the original source code and original license.
* You are not allowed to bundle it with any adware/malware/spyware or any addittional software content that installs together with the application even if there is possibility for end user to opt-out.
* You are not allowed to charge money for this application.

As this unfortunately happens relatively often, download hubs such as ZDNet, Brothersoft, Softpedia etc. are used to it and attempting any of the above would quickly get you banned from these sites.

**Special thanks goes to:**
* Davide Pizzolato, Author of CxImage Library.
* Armen Hakobyan, Export Dialog Modifications.
* Alvaro Mendez, AMSEdit Class.
* Andreas Saurwein, Console Redirect.
* Michael Dunn, Wonderful MFC Articles.

**IconMasterXP is using the following software:**
* Quantizer, ©1996-1997 Jeff Prosise.
* IJG JPEG library ©1994-1998 Thomas G. Lane.
* LibPNG v1.2.7 ©1998-2007 Glenn Randers-Pehrson.
* LibTIFF v3.5.7 ©1988-1997 Sam Leffler, ©1991-1997 Silicon Graphics Inc.
* LibMNG v1.0.10 ©2000-2002 Gerard Juyn.
* LibJ2K ©2001-2002 David Janssens.
* LibJBG v1.6 ©2004 Markus Kuhn.
* JasPer v1.900.1 ©2001-2007 Image Power, UBC, Michael David Adams.
* zlib v1.2.3 ©1995-2005 Jean-loup Gailly and Mark Adler.

Following is a table of licenses used by individual components.

| Component     | License                                     |
| ------------- |:------------------------------------------- |
| CxImage       | Zlib                                        |
| Jasper        | MIT                                         |
| JPeg          | JPeg (BSD-like)                             |
| MNG           | Custom (MIT-like)                           |
| PNG           | LibPNG (Zlib-like)                          |
| TIFF          | Custom (BSD-like)                           |
| Zlib          | Zlib                                        |
| JBig          | GPL (not used anywhere to this moment)      |

Continued below is the description of features and capabilities of this application, taken from this site.

## Description

IconMasterXP is a versatile app. It fully supports alpha transparency mask (also known as PNG mask), it can convert pictures into multi-paged icons, it has an easy to use batch-processing interface and supports Windows® Vista/7/8 icon format.

![Screenshot](http://iconmasterxp.com/scr1.png)
![Screenshot](http://iconmasterxp.com/scr2.png)


There is a whole set of special effects such as gamma, light, contrast, soften/sharpen, color balance etc. It can do geometric operations (rotate/resize) supporting five supersampling algorithms which you can use without breaking your alpha (or PNG transparency) mask. Besides 32-bit pictures, other types are supported (24, 8, 4 and 1 bpp) with editable palette and color dithering - it can downgrade or upgrade image bit-depth. It is designed for anyone who works with .ICO files from software developers to digital graphic designers.

### Supported Formats

| Format        | Import  | Export                |
|:-------------:|:-------:|:---------------------:|
| PNG           | Yes     | Yes                   |
| ICO           | Yes     | Yes                   |
| BMP, WBMP     | Yes     | Yes                   |
| GIF           | Yes     | No (licence probs)    |
| PSD           | Yes     | Yes (external util)   |
| TIFF          | Yes     | Yes                   |
| TGA           | Yes     | Yes                   |
| PCX           | Yes     | Yes                   |
| WMF           | Yes     | Yes                   |
| EMF           | Yes     | Yes (if source WMF)   |
| JPG, JP2      | Yes     | Yes                   |
