import { Injectable, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { CreateUserDto } from './dto/create-user.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { User, UserStatus } from './entities/user.entity';
import { Cron, CronExpression } from '@nestjs/schedule';

/*
Service separat the business logic from Controllers, helps make this logic reusabel throughour multiple parts of the app.
Service will be responsible for data storage and retrieval. will be used by the UsersController.
*/
@Injectable()
export class UsersService {

	constructor(
		@InjectRepository(User)
		private readonly userRepository: Repository<User>,
	) {}

	findAll() {
		return this.userRepository.find();
	}

	async findOneById(id: number) {
		return this.userRepository.findOneById(id);
	}

	async findById(idToFind: number): Promise<User> {
		const user = await this.userRepository.findOne({
			where: {id: idToFind}
		});
		return user;
	}
	async findByLogin(loginToFind: string) {
		const user = await this.userRepository.findOne({
			where: {login: loginToFind}
		});
		return user;
	}

	async findByNickname(nicknameToFind: string) {
		const user = await this.userRepository.findOne({
			where: {nickname: nicknameToFind}
		});
		return user;	
	}

	async checkTwoFA(nicknameToFind: string) {
		const user = await this.userRepository.findOne({
			where: {nickname: nicknameToFind}
		});
		return user.twoFacAuth;
	}

	createUser(createUserDto: CreateUserDto): Promise<User> {
		const user = this.userRepository.create(createUserDto);
		user.nickname = user.login;
		user.avatar = '';
		user.currentStatus = UserStatus.ONLINE;
		user.twoFacAuth = false;
		user.requestedFriends = [];
		user.friends = [];
		user.blockedUsers = [];
		user.lastActive = new Date();
		return this.userRepository.save(user);
	}

	async updateUser(id: number, updateUserDto: UpdateUserDto) {
		//preload() creates a new entity based on the object passed into it.
		//it first looks to see if an entity ALREADY exists in the database, and retrieves it and everything related to it.
		//if alreay exists, preload replaces all of the values with the new ones passed in here in our UpdatUserDto.
		const user = await this.userRepository.preload({
			id: +id,
			...updateUserDto,
		});
		if (!user) {
			//
		}
		user.lastActive = new Date();
		return this.userRepository.save(user);
	}

	async changeNickName(username: string, newNickName: string): Promise<boolean> {
		try {
		  const user = await this.findByLogin(username);
		  if (!user) {
			return false;
		  } else {
			user.nickname = newNickName;
			await this.updateUser(user.id, user);
		  }
		  return true;
		} catch (error) {
		  console.error('Error verifying secret key:', error);
		  return false;
		}
	}

	async findProfilePic(loginToFind: string) {
		const user = await this.userRepository.findOne({
			where: {login: loginToFind}
		});
		if (user && user.avatar) {
			const profilePicPath = `/app/uploads/${user.avatar}`;
    		return profilePicPath;
		} else {
			const profilePicPath = `/app/uploads/default.jpeg`;
    		return profilePicPath;
		}
	}

	async changeProfilePic(username: string, filename: string): Promise<boolean> {
		const user = await this.findByLogin(username);
		if (!user) {
		  return false;
		}
	
		user.avatar = filename;
		await this.updateUser(user.id, user);
		return true;
	}

	async removeUser(idToRemove: number) {
		const user = await this.findById(idToRemove); //this findOne() method was referenced from my own UsersService class.
		return this.userRepository.remove(user);
	}

	// Function to update the user's activity timestamp in memory.
	async updateUserActivity(id: number, status: number) {
		const user = await this.findById(id);
		user.lastActive = new Date();
		user.currentStatus = status;
		await this.updateUser(id, user);
	}

	// Cron to check every minute if user status should be changed to OFFLINE. 2 mins timeout.
	@Cron(CronExpression.EVERY_MINUTE)
	async checkCurrentStatus() {
		const currentTime = new Date();
		const inactiveThreshold = new Date(currentTime);
		inactiveThreshold.setMinutes(inactiveThreshold.getMinutes() - 2);

		const offlineUsers = await this.userRepository
		.createQueryBuilder('user')
		.where('user.lastActive <= :inactiveThreshold', { inactiveThreshold })
		.getMany();

		for (const user of offlineUsers) {
			user.currentStatus = UserStatus.OFFLINE;
			await this.updateUser(user.id, user);
		}
	}
}
