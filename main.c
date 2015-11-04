/*

File: main.c

Abstract: Contains the main entry point, globals, and event handling for
the ATSUIBasics sample.

Version: <1.0>

Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple
Computer, Inc. ("Apple") in consideration of your agreement to the
following terms, and your use, installation, modification or
redistribution of this Apple software constitutes acceptance of these
terms.  If you do not agree with these terms, please do not use,
install, modify or redistribute this Apple software.

In consideration of your agreement to abide by the following terms, and
subject to these terms, Apple grants you a personal, non-exclusive
license, under Apple's copyrights in this original Apple software (the
"Apple Software"), to use, reproduce, modify and redistribute the Apple
Software, with or without modifications, in source and/or binary forms;
provided that if you redistribute the Apple Software in its entirety and
without modifications, you must retain this notice and the following
text and disclaimers in all such redistributions of the Apple Software. 
Neither the name, trademarks, service marks or logos of Apple Computer,
Inc. may be used to endorse or promote products derived from the Apple
Software without specific prior written permission from Apple.  Except
as expressly stated in this notice, no other rights or licenses, express
or implied, are granted by Apple herein, including but not limited to
any patent rights that may be infringed by your derivative works or by
other works in which the Apple Software may be incorporated.

The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.

IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

Copyright © 2004-2007 Apple Inc., All Rights Reserved

*/ 

#include "main.h"
#include "helloworld.h"
#include "multiplestyles.h"
#include "fontsubstitution.h"
#include "verticaltext.h"
#include "paragraphs.h"

#define kHelloWorldHIViewSignature			'Wnd1'
#define kHelloWorldHIViewFieldID			1
#define kMultipleStylesHIViewSignature		'Wnd2'
#define kMultipleStylesHIViewFieldID		2
#define kFontSubstitutionHIViewSignature	'Wnd3'
#define kFontSubstitutionHIViewFieldID		3
#define kVerticalTextHIViewSignature		'Wnd4'
#define kVerticalTextHIViewFieldID			4
#define kParagraphsHIViewSignature			'Wnd5'
#define kParagraphsHIViewFieldID			5

// Main entry point
//
int main(int argc, char* argv[])
{
	WindowRef		helloWorldWindow;
	WindowRef		multipleStylesWindow;
	WindowRef		fontSubtitutionWindow;
	WindowRef		verticalTextWindow;
	WindowRef		paragraphsWindow;
	
	HIViewRef		helloWorldView;
	HIViewRef		multipleStylesView;
	HIViewRef		fontSubtitutionView;
	HIViewRef		verticalTextView;
	HIViewRef		paragraphsView;
	
    IBNibRef 		nibRef;
    OSStatus		err = noErr;

    static const EventTypeSpec kMyEvents[] =		{ { kEventClassControl, kEventControlDraw } };

	static const HIViewID helloWorldViewID =		{ kHelloWorldHIViewSignature, kHelloWorldHIViewFieldID };
	static const HIViewID multipleStylesViewID =	{ kMultipleStylesHIViewSignature, kMultipleStylesHIViewFieldID };
	static const HIViewID fontSubstitutionViewID =	{ kFontSubstitutionHIViewSignature, kFontSubstitutionHIViewFieldID };
	static const HIViewID verticalTextViewID =		{ kVerticalTextHIViewSignature, kVerticalTextHIViewFieldID };
	static const HIViewID paragraphsViewID =		{ kParagraphsHIViewSignature, kParagraphsHIViewFieldID };

    // Get the GUI resources from the NIB file
    err = CreateNibReference(CFSTR("main"), &nibRef);
    require_noerr( err, CantGetNibRef );
    
    // Set up the global menubar
    err = SetMenuBarFromNib(nibRef, CFSTR("MenuBar"));
    require_noerr( err, CantSetMenuBar );
    
    // *** Create the "Hello World!" window, make it visible, draw its contents
    err = CreateWindowFromNib(nibRef, CFSTR("HelloWorldWindow"), &helloWorldWindow);
    require_noerr( err, CantCreateWindow );
	HIViewFindByID( HIViewGetRoot( helloWorldWindow ), helloWorldViewID, &helloWorldView );
	err = HIViewInstallEventHandler( helloWorldView, NewEventHandlerUPP( HelloWorldEventHandler ), GetEventTypeCount( kMyEvents ), kMyEvents, ( void * ) helloWorldView, NULL );
    ShowWindow(helloWorldWindow);

    // *** Create the Multiple Styles window, make it visible, draw its contents
    err = CreateWindowFromNib(nibRef, CFSTR("MultipleStylesWindow"), &multipleStylesWindow);
    require_noerr( err, CantCreateWindow );
	HIViewFindByID( HIViewGetRoot( multipleStylesWindow ), multipleStylesViewID, &multipleStylesView );
	err = HIViewInstallEventHandler( multipleStylesView, NewEventHandlerUPP( MultipleStylesEventHandler ), GetEventTypeCount( kMyEvents ), kMyEvents, ( void * ) multipleStylesView, NULL );
    ShowWindow(multipleStylesWindow);

    // *** Create the Font Substitution window, make it visible, draw its contents
    err = CreateWindowFromNib(nibRef, CFSTR("FontSubstitutionWindow"), &fontSubtitutionWindow);
    require_noerr( err, CantCreateWindow );
	HIViewFindByID( HIViewGetRoot( fontSubtitutionWindow ), fontSubstitutionViewID, &fontSubtitutionView );
	err = HIViewInstallEventHandler( fontSubtitutionView, NewEventHandlerUPP( FontSubstitutionWindowEventHandler ), GetEventTypeCount( kMyEvents ), kMyEvents, ( void * ) fontSubtitutionView, NULL );
    ShowWindow(fontSubtitutionWindow);

    // *** Create the Vertical Text window, make it visible, draw its contents
    err = CreateWindowFromNib(nibRef, CFSTR("VerticalTextWindow"), &verticalTextWindow);
	HIViewFindByID( HIViewGetRoot( verticalTextWindow ), verticalTextViewID, &verticalTextView );
	err = HIViewInstallEventHandler( verticalTextView, NewEventHandlerUPP( VerticalTextWindowEventHandler ), GetEventTypeCount( kMyEvents ), kMyEvents, ( void * ) verticalTextView, NULL );
    require_noerr( err, CantCreateWindow );
    ShowWindow(verticalTextWindow);

    // *** Create the Paragraphs window, make it visible, set up and draw its contents for the first time
    err = CreateWindowFromNib(nibRef, CFSTR("ParagraphsWindow"), &paragraphsWindow);
    require_noerr( err, CantCreateWindow );
	SetUpParagraphsContents(paragraphsWindow);
	HIViewFindByID( HIViewGetRoot( paragraphsWindow ), paragraphsViewID, &paragraphsView );
	err = HIViewInstallEventHandler( paragraphsView, NewEventHandlerUPP( ParagraphsWindowEventHandler ), GetEventTypeCount( kMyEvents ), kMyEvents, ( void * ) paragraphsView, NULL );
    ShowWindow(paragraphsWindow);

    DisposeNibReference(nibRef);
    
    // Call the event loop
    RunApplicationEventLoop();

CantCreateWindow:
CantSetMenuBar:
CantGetNibRef:
	return err;
}
