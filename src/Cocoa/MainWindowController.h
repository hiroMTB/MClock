//
//  MainWindowController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

@class dt_GLView;

@interface MainWindowController : NSWindowController {
    IBOutlet dt_GLView *glView;
}

@end
