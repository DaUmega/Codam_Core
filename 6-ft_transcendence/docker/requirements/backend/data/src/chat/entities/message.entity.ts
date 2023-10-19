import {
  Entity,
  Column,
  CreateDateColumn,
  PrimaryGeneratedColumn,
  ManyToOne,
  JoinTable
} from 'typeorm'

import { IsNotEmpty } from 'class-validator'
import { User } from '../../users/entities/user.entity'

@Entity()
export class Message {
  @PrimaryGeneratedColumn()
  id: number

  @Column()
  @IsNotEmpty()
  text: string

  @ManyToOne(() => User, { eager: true })
  sender: User;

  @CreateDateColumn()
  createdAt!: Date;
}
