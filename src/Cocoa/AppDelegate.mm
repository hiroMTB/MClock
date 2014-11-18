#import "AppDelegate.h"
#import "MainWindowController.h"

@implementation AppDelegate

@synthesize mainWindowController;

- (void)dealloc {
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    if( !mainWindowController ){
        mainWindowController = [[MainWindowController alloc] initWithWindowNibName:@"MainWindow"];
        [mainWindowController showWindow:self];
        
        NSLog(@"AppDelegate::applicationDidFinishLaunching");
        [self update_ui];
    }
}


@end
