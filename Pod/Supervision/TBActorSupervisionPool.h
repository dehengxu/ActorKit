//
//  TBActorSupervisionPool.h
//  ActorKitSupervision
//
//  Created by Julian Krumow on 11.10.15.
//  Copyright (c) 2015 Julian Krumow. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TBActorSupervisor.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  This class represents a supervision pool which manages the lifecyle of registered actors.
 *
 *  When an actor is put under supervision it is reachable via a unique ID.
 *
 *  In case of a crash the actor will be replaced with a new instance. Unprocessed messages will remain
 *  inside the actor's mailbox and will be executed on the new instance as soon as it is ready.
 *
 *  Actors can be linked to ensure that they will be re-created alongside the crashed actor.
 */
@interface TBActorSupervisionPool : NSObject

/**
 *  The receiver returns a singleton instance of a supervision pool.
 *
 *  @return The singleton instance.
 */
+ (instancetype)sharedInstance;

/**
 *  Creates an actor and adds it to the supervision pool.
 *
 *  @exception Throws an exception when an ID is already in use.
 *
 *  @param Id            The ID of the actor to create.
 *  @param creationBlock The block to create the actor.
 */
- (void)superviseWithId:(NSString *)Id creationBlock:(TBActorCreationBlock)creationBlock;

/**
 *  Removes a specified actor and all linked actors from the supervision pool.
 *
 *  @param Id The ID of the actor to remove.
 */
- (void)unsuperviseActorWithId:(NSString *)Id;

/**
 *  Links two actors by their IDs. If the parent actor crashes, the given supervisor
 *  will re-create the linked actors as well.
 *
 *  @exception Throws an exception when linking would cause circular references.
 *
 *  @param actorId       The actor to link.
 *  @param parentActorId The parent actor to link to.
 */
- (void)linkActor:(NSString *)actorId toParentActor:(NSString *)parentActorId;

/**
 *  Unlinks two linked actors by their IDs.
 *
 *  @exception Throws an exception when link does not exist.
 *
 *  @param actorId       The actor to unlink.
 *  @param parentActorId The parent actor to unlink from.
 */
- (void)unlinkActor:(NSString *)actorId fromParentActor:(NSString *)parentActorId;

/**
 *  Returns the ID of a given actor instance
 *
 *  @param actor The actor instance.
 *
 *  @return The ID of the given actor instance. Can be nil if actor does not exist.
 */
- (nullable NSString *)idForActor:(NSObject *)actor;

/**
 *  Returns supervisors for a given set actor ids.
 *
 *  @param Ids A set of actor IDs.
 *
 *  @return An array containing all supervisors.
 */
- (NSArray *)supervisorsForIds:(NSSet *)Ids;

/**
 *  Tells supervisors to recreate their actors for a given set actor ids.
 *
 *  @param Ids A set of actor IDs.
 */
- (void)updateSupervisorsWithIds:(NSSet *)Ids;

- (nullable id)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key;
@end
NS_ASSUME_NONNULL_END
