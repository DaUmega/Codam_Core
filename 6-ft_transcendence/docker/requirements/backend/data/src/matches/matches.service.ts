import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { CreateMatchDto } from './dto/create-match.dto';
import { Match } from './entities/match.entity';

@Injectable()
export class MatchesService {
	constructor(
		@InjectRepository(Match)
		private readonly matchRepository: Repository<Match>,
	) {}

	findAll() {
		return this.matchRepository.find();
	}

	async findUserAll(id: number): Promise<Match[]> {
        return this.matchRepository
            .createQueryBuilder('match')
            .where('match.playerOneId = :id OR match.playerTwoId = :id', { id })
            .getMany();
    }

	createMatch(createMatchDto: CreateMatchDto) {
		const match = this.matchRepository.create(createMatchDto);
		return this.matchRepository.save(match);
	}
}
