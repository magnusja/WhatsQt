/*
 * This file is part of WhatsQt.
 *
 * WhatsQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WhatsQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WhatsQt.  If not, see <http://www.gnu.org/licenses/>.
 */

#import <Foundation/Foundation.h>

// TODO: maybe implement some delegate pattern in C++ -> no knowledge of actual OSXNotificationService
// but abstract class which OSXNotificationService can then implement
class OSXNotificationService;

@interface NotificationCenterDelegate : NSObject<NSUserNotificationCenterDelegate>
- (id)initWithNotificationService:(OSXNotificationService *)notificationService;
@end
