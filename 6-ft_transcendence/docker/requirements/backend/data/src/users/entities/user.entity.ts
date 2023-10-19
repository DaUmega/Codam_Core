import { Column, Entity, JoinTable, ManyToMany, PrimaryGeneratedColumn } from "typeorm";

/*
by default, TypeOrm will name SQL table based on the class name in lower case.
so the generated SQL table will be "user".
if I want to use a different name, I can specify inside the @Entity() decorator. eg: @Entity('users')
*/
@Entity()
export class User {
	//with this decorator, it define the id as the primary column AND auto increment.
	@PrimaryGeneratedColumn()
	id?: number;

	@Column({unique: true})
	login: string;

	@Column({unique: true, nullable: true})
	nickname: string;

	@Column()
	avatar: string;

	// https://stackoverflow.com/questions/43747765/self-referencing-manytomany-relationship-typeorm
	@ManyToMany(() => User)
	@JoinTable({ joinColumn: { name: 'senderId' }})
	requestedFriends: User[];

	@ManyToMany(() => User, { cascade: true})
	@JoinTable({ joinColumn: { name: 'userOneId' }})
	friends: User[];

	@ManyToMany(() => User, { cascade: true})
	@JoinTable({ joinColumn: { name: 'userOneId' }})
	blockedUsers: User[];

	@Column()
	currentStatus: number;

	@Column()
	twoFacAuth: boolean;

	@Column({ nullable: true })
	twoFactorSecret: string;

	@Column({ type: "timestamp", default: () => "CURRENT_TIMESTAMP" })
    lastActive: Date;

	//TypeOrm now knows that flavor should store array's as json
	//and "nullable" make this column optional in the table.
	//@Column('json', {nullable: true})
	//friends: number[]; //??? not sure if it is a good way to represent a list of friens, because it is dynamic. friends need to be deleteable.

}

export enum UserStatus {
	ONLINE = 1,
	OFFLINE = 2,
	IN_A_GAME = 3,
}