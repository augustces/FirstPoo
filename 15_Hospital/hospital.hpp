#include <iostream>
#include <sstream>
#include <exception>
#include <map>
#include<memory>

class IMedico;

class IPaciente {
    public:
    virtual void addMedico(std::shared_ptr<IMedico> medico) = 0;
    virtual std::string getDiagnostico() const = 0;
    virtual std::string getId() const = 0;
    virtual std::map<std::string, std::shared_ptr<IMedico>> getMedicos( ) const = 0;
    virtual void removerMedico(std::string id) = 0;
    virtual ~IPaciente(){};
};

class IMedico {
    public:
    virtual void addPaciente(std::shared_ptr<IPaciente> paciente) = 0;
    virtual std::string getClasse() const = 0;
    virtual std::string getId() const = 0;
    virtual std::map<std::string, std::shared_ptr<IPaciente>> getPacientes() const = 0;
    virtual void removerPaciente(std::string id) = 0;
    virtual ~IMedico(){};
};

class Paciente : public IPaciente {
    std::string diagnostico{""};
    std::map<std::string, std::shared_ptr<IMedico>> medicos;
    std::string sender{""};
    public:
    Paciente (std::string sender, std::string diagnostico);
    void addMedico(std::shared_ptr<IMedico> medico) override;
    std::string getDiagnostico() const override;
    std::string getId() const override;
    std::map<std::string, std::shared_ptr<IMedico>> getMedicos() const override;
    void removerMedico(std::string id) override;
    friend std::ostream& operator<<(std::ostream& os, std::shared_ptr<IPaciente> p);
};

class Medico : public IMedico {
    std::string classe{""};
    std::string sender{""};
    std::map<std::string, std::shared_ptr<IPaciente>> pacientes;
    public:
    Medico(std::string sender, std::string classe);
    void addPaciente (std::shared_ptr<IPaciente> paciente) override;
    std::string getClasse() const override;
    std::string getId() const override;
    std::map<std::string, std::shared_ptr<IPaciente>> getPacientes() const override;
    void removerPaciente(std::string id) override;
    friend std::ostream& operator<<(std::ostream& os, std::shared_ptr<IMedico> m);
};

class Hospital {
    std::map<std::string, std::shared_ptr<IMedico>> medicos;
    std::map<std::string, std::shared_ptr<IPaciente>> pacientes;
    public:
    Hospital();
    void addMedico(std::shared_ptr<IMedico> medico);
    void addPaciente (std::shared_ptr<IPaciente> paciente);
    void removerMedico(std::string id);
    void removerPaciente(std::string id);
    void vincular (std::string medicoId, std::string PacienteId);
    friend std::ostream& operator<<(std::ostream& os, Hospital* h);
};