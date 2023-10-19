import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity()
export class Match {
	@PrimaryGeneratedColumn()
	matchId: number;

	@Column()
	playerOneId: number;

	@Column()
	playerTwoId: number;

	@Column()
	winnerId: number;
}