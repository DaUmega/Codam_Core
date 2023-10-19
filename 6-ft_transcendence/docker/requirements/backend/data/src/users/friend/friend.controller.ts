import { Body, Controller, Get, HttpException, HttpStatus, Param, ParseIntPipe, Post, Query } from '@nestjs/common';
import { User } from '../entities/user.entity';
import { UsersService } from '../users.service';
import { EditFriendActionType, FriendDto } from './dto/edit-friend.dto';
import { FriendService } from './friend.service';

const apiKey = process.env.VUE_APP_SECRET;

@Controller(`${apiKey}/friend`)
export class FriendController {
	constructor(
		private readonly friendService: FriendService,
		private readonly usersService: UsersService,
	) {}

	//http://localhost:3000/api/friend/are-friends?idOne=1&idTwo=2
	@Get('are-friends')
	async areFriends(
		@Query('idOne', ParseIntPipe) idOne: number,
		@Query('idTwo', ParseIntPipe) idTwo: number,
	) {
		return await this.friendService.areFriends(idOne, idTwo);
	}

	//http://localhost:3000/api/friend/friend-request?id=1
	@Get('friend-request?')
	async getFriendRequest(@Query('id', ParseIntPipe) id: number) {
		return await this.friendService.getReceivedFriendRequests(id);
	}

	//http://localhost:3000/api/friend/friend-list?id=1
	@Get('friend-list?')
	async getFriendList(@Query('id', ParseIntPipe) id: number) {
		return await this.friendService.getFriends(id);
	}

	//http://localhost:3000/api/friend/edit-friend
	@Post('edit-friend')
	async editFriend(@Body() friendDto: FriendDto) {
		// check if both users exist
		const user: User = await this.usersService.findById(friendDto.userId);
		const friend: User = await this.usersService.findById(friendDto.friendId);
		if (!user || !friend) {
			throw new HttpException(
				'User or friend does not exist',
				HttpStatus.BAD_REQUEST,
			);
		}
		// check current friend status between two users
		const areFriends = await this.friendService.areFriends(friendDto.userId, friendDto.friendId,);
		// if action is delete friend
		if (friendDto.action == EditFriendActionType.REMOVE_FRIEND) {
			if (areFriends) {
				await this.friendService.removeFriend(user, friend);
				await this.friendService.removeFriend(friend, user);
			} else {
				throw new HttpException(
					'User and requested user are not friends.',
					HttpStatus.UNAUTHORIZED,
				);
			}
		} 
		else {
			if (areFriends) {
				throw new HttpException(
					'User and requested user are already friends.',
					HttpStatus.UNAUTHORIZED,
				);
			} else {
				// check current request status between two users
				const isUserReceivedRequest =
					await this.friendService.isUserRequested(friendDto.userId, friendDto.friendId);
				const isUserSendRequest =
					await this.friendService.isUserRequested(friendDto.friendId, friendDto.userId );
				// if action is send friend request
				if (friendDto.action === EditFriendActionType.SEND_FRIEND_REQUEST) {
					if (isUserSendRequest) {
						throw new HttpException(
							'Request has already sent by this user.',
							HttpStatus.BAD_REQUEST,
						);
					} else if (isUserReceivedRequest) {
						throw new HttpException(
							'Request has arealdy been sent by the other user.',
							HttpStatus.BAD_REQUEST,
						);
					} else {
						await this.friendService.addFriendRequest(user, friend);
					}
				} else {
					if (isUserReceivedRequest) {
						// for either ADD_FRIEND or REJECT_REQUEST, need to remove request
						await this.friendService.removeFriendRequest(friend, user);
						if (friendDto.action === EditFriendActionType.ADD_FRIEND) {
							await this.friendService.addFriend(user, friend);
							await this.friendService.addFriend(friend, user);
						}
					} else {
						throw new HttpException(
							'User is not authorization',
							HttpStatus.UNAUTHORIZED,
						);
					}
				}
			}
		}
	}
}
