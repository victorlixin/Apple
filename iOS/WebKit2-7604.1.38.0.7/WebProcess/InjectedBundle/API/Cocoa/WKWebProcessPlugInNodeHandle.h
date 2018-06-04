/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <WebKit/WKFoundation.h>

#if WK_API_ENABLED

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>
#import <WebKit/WKImage.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#endif

@class WKWebProcessPlugInFrame;

WK_CLASS_AVAILABLE(macosx(10.10), ios(8.0))
@interface WKWebProcessPlugInNodeHandle : NSObject

+ (WKWebProcessPlugInNodeHandle *)nodeHandleWithJSValue:(JSValue *)value inContext:(JSContext *)context;
- (WKWebProcessPlugInFrame *)htmlIFrameElementContentFrame;

#if TARGET_OS_IPHONE
- (UIImage *)renderedImageWithOptions:(WKSnapshotOptions)options WK_API_AVAILABLE(macosx(10.11), ios(9.0));
- (UIImage *)renderedImageWithOptions:(WKSnapshotOptions)options width:(NSNumber *)width WK_API_AVAILABLE(macosx(WK_MAC_TBA), ios(WK_IOS_TBA));
#else
- (NSImage *)renderedImageWithOptions:(WKSnapshotOptions)options WK_API_AVAILABLE(macosx(10.11), ios(9.0));
- (NSImage *)renderedImageWithOptions:(WKSnapshotOptions)options width:(NSNumber *)width WK_API_AVAILABLE(macosx(WK_MAC_TBA), ios(WK_IOS_TBA));
#endif

@property (nonatomic, readonly) CGRect elementBounds;
@property (nonatomic) BOOL HTMLInputElementIsAutoFilled;
@property (nonatomic, readonly) BOOL HTMLInputElementIsUserEdited;
@property (nonatomic, readonly) BOOL HTMLTextAreaElementIsUserEdited;
@property (nonatomic, readonly) WKWebProcessPlugInNodeHandle *HTMLTableCellElementCellAbove;
@property (nonatomic, readonly) WKWebProcessPlugInFrame *frame;

- (BOOL)isTextField;

@end

#endif // WK_API_ENABLED