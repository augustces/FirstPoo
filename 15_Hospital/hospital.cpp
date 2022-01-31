#include "hospital.hpp"

//Paciente
Paciente::Paciente (std::string sender, std::string diagnostico) {
    this->sender = sender;
    this->diagnostico = diagnostico;
}

void Paciente::addMedico(std::shared_ptr<IMedico> medico) {
    auto it = medicos.find(medico->getId());
    for (auto& i : medicos) {
        if (i.second->getClasse() == medico->getClasse())
            throw std::runtime_error("fail: ja existe outro medico da especialidade " + medico->getClasse());
    }
    if (it != medicos.end())
        throw std::runtime_error("fail: o medico ja foi adicionado");

    medicos.insert(std::make_pair(medico->getId(), medico));
}

std::string Paciente::getDiagnostico() const{
    return this->diagnostico;
}

std::string Paciente::getId() const{
    return this->sender;
}

std::map<std::string, std::shared_ptr<IMedico>> Paciente::getMedicos() const{
    return this->medicos;
}

void Paciente::removerMedico(std::string id) {
    auto it = medicos.find(id);
    if (it == medicos.end())
        throw std::runtime_error("fail: medico nao existe");

    medicos.erase(id);
}

std::ostream& operator<<(std::ostream& os, std::shared_ptr<IPaciente> p){
    os << p->getId() << ':' << p->getDiagnostico();
    os << "     Meds: [ ";
    auto medicos = p->getMedicos();
    for (auto& obj : medicos) {
        os << obj.first << " ";
    }
    os << "]";
    return os;
}

//Medico
Medico::Medico(std::string sender, std::string classe) {
    this->sender = sender;
    this->classe = classe;
}

void Medico::addPaciente (std::shared_ptr<IPaciente> paciente) {
    auto it = this->pacientes.find(paciente->getId());

    if (it != this->pacientes.end())
        throw std::runtime_error("fail: paciente ja acompanhado");

    this->pacientes.insert(std::make_pair(paciente->getId(), paciente));
}
 
std::string Medico::getClasse() const {
    return this->classe;
}

std::string Medico::getId() const {
    return this->sender;
}

std::map<std::string, std::shared_ptr<IPaciente>> Medico::getPacientes() const {
    return this->pacientes;
}

void Medico::removerPaciente(std::string id) {
    auto it = this->pacientes.find(id);
    if (it == this->pacientes.end()) 
        throw std::runtime_error("fail: paciente nao encontrado");
    
    this->pacientes.erase(id);
}

std::ostream& operator<<(std::ostream& os, std::shared_ptr<IMedico> m){
    os << m->getId() << ':' << m->getClasse();
    os << "     Pacs: [ ";
    auto pacientes =  m->getPacientes();
    for (auto& obj : pacientes) {
        os << obj.first << " ";
    }
    os << "]";
    return os;
}

//Hospital
Hospital::Hospital() {}

void Hospital::addMedico(std::shared_ptr<IMedico> medico) {
    auto it = medicos.find(medico->getId());

    if (it != medicos.end())
        throw std::runtime_error("fail: o medico ja foi adicionado");

    medicos.insert(std::make_pair(medico->getId(), medico));
}

void Hospital::addPaciente (std::shared_ptr<IPaciente> paciente) {
    auto it = this->pacientes.find(paciente->getId());

    if (it != this->pacientes.end())
        throw std::runtime_error("fail: paciente ja adicionado");

    this->pacientes.insert(std::make_pair(paciente->getId(), paciente));
}

void Hospital::removerMedico(std::string id) {
    auto it = medicos.find(id);
    if (it == medicos.end())
        throw std::runtime_error("fail: medico nao existe");

    medicos.erase(id);
}

void Hospital::removerPaciente(std::string id) {
    auto it = this->pacientes.find(id);
    if (it == this->pacientes.end()) 
        throw std::runtime_error("fail: paciente nao encontrado");
    
    this->pacientes.erase(id);
}

void Hospital::vincular (std::string medicoId, std::string PacienteId) {
    auto it = this->medicos.find(medicoId);
    auto pac = this->pacientes.find(PacienteId);
    if (it != medicos.end() && pac != pacientes.end()) {
        pac->second->addMedico(it->second);
        it->second->addPaciente(pac->second);
    }   
}

std::ostream& operator<<(std::ostream& os, Hospital* h){
    for (auto& obj : h->pacientes) {
        os << "Pac: " << obj.second << '\n';
    }
    for (auto& obj : h->medicos) {
        os << "Med: " << obj.second << '\n';
    }
    return os;
}