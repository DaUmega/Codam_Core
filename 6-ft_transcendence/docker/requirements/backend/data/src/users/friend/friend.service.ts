import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from '../entities/user.entity';

@Injectable()
export class FriendService {
	constructor(
		@InjectRepository(User)
		private readonly userRepository: Repository<User>,
	) {}

	
	async areFriends(idOne: number, idTwo: number): Promise<boolean> {
		const areFriends = await this.userRepository
		.createQueryBuilder('user')
		.leftJoinAndSelect('user.friends', 'friend')
		.where('friend.id = :idOne', { idOne })
		.andWhere('user.id = :idTwo', { idTwo })
		.getOne();
		return !(areFriends == undefined)
	}

	async isUserRequested(userId: number, senderId: number): Promise<boolean> {
		const request = await this.userRepository
			.createQueryBuilder('user')
			.leftJoinAndSelect('user.requestedFriends', 'requested')
			.where('requested.id = :userId', { userId })
			.andWhere('user.id = :senderId', { senderId })
			.getOne();
		return !(request == undefined);
	}

	async addFriendRequest(sender: User, receiver: User) {
		sender.requestedFriends = await this.getSentFriendRequests(sender.id);
		if (!sender.requestedFriends) {
			sender.requestedFriends = [];
		}
		sender.requestedFriends.push(receiver);
		await this.userRepository.save(sender);
	}

	async removeFriendRequest(sender: User, receiver: User) {
		const requestedFriends = await this.getReceivedFriendRequests(
			sender.id,
		);
		if (requestedFriends) {
			sender.requestedFriends = requestedFriends.filter((request) => {
				return request.id !== receiver.id;
			});
			await this.userRepository.save(sender);
		}
	}

	async addFriend(user: User, friendToAdd: User) {
		user.friends = await this.getFriends(user.id);
		if (!user.friends) {
			user.friends = [];
		}
		user.friends.push(friendToAdd);
		await this.userRepository.save(user);
	}

	async removeFriend(user: User, friendToRemove: User) {
		const friends = await this.getFriends(user.id);
		if (friends) {
			user.friends = friends.filter((friend) => {
				return friend.id !== friendToRemove.id;
			});
			await this.userRepository.save(user);
		}
	}

	async getFriends(userId: number): Promise<User[]> {
		const user = await this.userRepository
			.createQueryBuilder('user')
			.leftJoinAndSelect('user.friends', 'friend')
			.where('user.id = :userId', { userId })
			.getOne();
		return user.friends;
	}

	async getReceivedFriendRequests(userId: number): Promise<User[]> {
		const friendRequests = await this.userRepository
			.createQueryBuilder('user')
			.leftJoinAndSelect('user.requestedFriends', 'requested')
			.where('requested.id = :userId', { userId })
			.getMany();
		return friendRequests;
	}

	async getSentFriendRequests(userId: number): Promise<User[]> {
		const user = await this.userRepository
			.createQueryBuilder('user')
			.leftJoinAndSelect('user.requestedFriends', 'requested')
			.where('user.id = :userId', { userId })
			.getOne();
		return user.requestedFriends;
	}
}
