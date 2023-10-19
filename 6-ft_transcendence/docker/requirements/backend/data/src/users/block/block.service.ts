import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from '../entities/user.entity';

@Injectable()
export class BlockService {
	constructor(
		@InjectRepository(User)
		private readonly userRepository: Repository<User>,
	) {}

	
	async areBlocked(idOne: number, idTwo: number): Promise<number> {
		const areBlockedOneToTwo = await this.userRepository
			.createQueryBuilder('user')
			.leftJoinAndSelect('user.blockedUsers', 'blocked')
			.where('blocked.id = :idOne', { idOne })
			.andWhere('user.id = :idTwo', { idTwo })
			.getOne();

		if (areBlockedOneToTwo) {
			return idTwo;
		}

		const areBlockedTwoToOne = await this.userRepository
			.createQueryBuilder('user')
			.leftJoinAndSelect('user.blockedUsers', 'blocked')
			.where('blocked.id = :idTwo', { idTwo })
			.andWhere('user.id = :idOne', { idOne })
			.getOne();

		if (areBlockedTwoToOne) {
			return idOne;
		} else {
			return 0;
		}
	}

	async getBlocked(idOne: number) {
		return this.userRepository
			.createQueryBuilder('user')
			.leftJoinAndSelect('user.blockedUsers', 'blocked')
			.where('blocked.id = :idOne OR user.id = :idOne', { idOne })
			.getMany();
	}

	async addBlock(user: User, userToBlock: User) {
		user.blockedUsers = await this.getBlocks(user.id);
		if (!user.blockedUsers) {
			user.blockedUsers = [];
		}
		user.blockedUsers.push(userToBlock);
		await this.userRepository.save(user);
	}

	async unBlock(user: User, userToUnblock: User) {
		const blocks = await this.getBlocks(user.id);
		if (blocks) {
			user.blockedUsers = blocks.filter((friend) => {
				return friend.id !== userToUnblock.id;
			});
			await this.userRepository.save(user);
		}
	}

	async getBlocks(userId: number): Promise<User[]> {
		const user = await this.userRepository
			.createQueryBuilder('user')
			.leftJoinAndSelect('user.blockedUsers', 'block')
			.where('user.id = :userId', { userId })
			.getOne();
		return user.blockedUsers;
	}
}
